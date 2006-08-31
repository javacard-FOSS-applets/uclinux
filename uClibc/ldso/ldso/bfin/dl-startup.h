     /* Copyright (C) 2003 Red Hat, Inc.
	Contributed by Alexandre Oliva <aoliva@redhat.com>

This file is part of uClibc.

uClibc is free software; you can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License as
published by the Free Software Foundation; either version 2.1 of the
License, or (at your option) any later version.

uClibc is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with uClibc; see the file COPYING.LIB.  If not, write to
the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139,
USA.  */
	
/* Any assembly language/system dependent hacks needed to setup
 * boot1.c so it will work as expected and cope with whatever platform
 * specific wierdness is needed for this architecture.

 * We override the default _dl_boot function, and replace it with a
 * bit of asm.  Then call the real _dl_boot function, which is now
 * named _dl_boot2.  */

/* At program start-up, p0 contains a pointer to a
   elf32_fdpic_loadmap that describes how the executable was loaded
   into memory.  p1 contains a pointer to the interpreter (our!)
   loadmap, if there is an interpreter, or 0 if we're being run as an
   executable.  p2 holds a pointer to the interpreter's dynamic
   section, if there is an interpreter, or to the executable's dynamic
   section, otherwise.  If the executable is not dynamic, gr18 is 0.

   We rely on the fact that the linker adds a pointer to the
   _GLOBAL_OFFSET_TABLE_ as the last ROFIXUP entry, and that
   __self_reloc returns the relocated pointer to us, so that we can
   use this value to initialize the PIC register.  */

asm("" \
    "	.text\n"			\
    "	.global	__dl_boot\n"		\
    "	.type	__dl_boot,@function\n"	\
    "__dl_boot:\n"			\
    "	call	.Lcall\n"		\
    ".Lcall:\n"				\
    "	R4 = RETS;\n"			\
    "	SP += -32;\n"			\
    "	R5 = P0;\n"			\
    "	R6 = P1;\n"			\
    "	R7 = P2;\n"			\
    "	R0.L = .Lcall;\n"		\
    "	R0.H = .Lcall;\n"		\
    "	R1.L = __ROFIXUP_LIST__;\n"	\
    "	R1.H = __ROFIXUP_LIST__;\n"	\
    "	R2.L = __ROFIXUP_END__;\n"	\
    "	R2.H = __ROFIXUP_END__;\n"	\
    "	R1 = R1 - R0;\n"		\
    "	R1 = R1 + R4;\n"		\
    "	R2 = R2 - R0;\n"		\
    "	R2 = R2 + R4;\n"		\
    "	R0 = P1;\n"			\
    "	CC = R0 == 0;\n"		\
    "	IF CC R0 = P0;\n"		\
    "	CALL	___self_reloc;\n"	\
    "	P3 = R0;\n"			\
    "	R1 = R5;\n"			\
    "	R2 = R6;\n"			\
    "	[SP + 12] = R7;\n"		\
    "	P0 = SP;\n"			\
    "	P0 += 24;\n"			\
    "	[SP + 16] = P0;\n"		\
    "	P0 += 12;\n"			\
    "	[SP + 20] = P0;\n"		\
    "	CALL	__dl_start;\n"		\
    "	P4 = [SP + 24];\n"		\
    "	P3 = [SP + 28];\n"		\
    "	P0 = R5;\n"			\
    "   SP += 32;\n"			\
    "	/* Pass our FINI ptr() to the user in P1 */\n"	\
    "	P1 = [P3 + __dl_fini@FUNCDESC_GOT17M4];\n" \
    "   JUMP (P4);\n"			\
    "	.size	__dl_boot,.-__dl_boot\n"
);

#define DL_BOOT(X)   \
static void  __attribute__ ((used)) \
_dl_start (Elf32_Addr dl_boot_got_pointer, \
	   struct elf32_fdpic_loadmap *dl_boot_progmap, \
	   struct elf32_fdpic_loadmap *dl_boot_ldsomap, \
	   Elf32_Dyn *dl_boot_ldso_dyn_pointer, \
	   struct funcdesc_value *dl_main_funcdesc, \
	   X)

struct elf32_fdpic_loadmap;

/*
 * Get a pointer to the argv array.  On many platforms this can be just
 * the address if the first argument, on other platforms we need to
 * do something a little more subtle here.
 */
#define GET_ARGV(ARGVP, ARGS) ARGVP = ((unsigned long*) ARGS)

/*
 * Compute the GOT address.  On several platforms, we use assembly
 * here.  on FR-V FDPIC, there's no way to compute the GOT address,
 * since the offset between text and data is not fixed, so we arrange
 * for the assembly _dl_boot to pass this value as an argument to
 * _dl_boot.  */
#define DL_BOOT_COMPUTE_GOT(got) ((got) = dl_boot_got_pointer)

#define DL_BOOT_COMPUTE_DYN(dpnt, got, load_addr) \
  ((dpnt) = dl_boot_ldso_dyn_pointer)

/*
 * Here is a macro to perform a relocation.  This is only used when
 * bootstrapping the dynamic loader.  RELP is the relocation that we
 * are performing, REL is the pointer to the address we are relocating.
 * SYMBOL is the symbol involved in the relocation, and LOAD is the
 * load address.
 */
#define PERFORM_BOOTSTRAP_RELOC(RELP,REL,SYMBOL,LOAD,SYMTAB) \
	switch(ELF32_R_TYPE((RELP)->r_info)){				\
	case R_BFIN_byte4_data:							\
	  *(REL) += (SYMBOL);						\
	  break;							\
	case R_BFIN_FUNCDESC_VALUE:					\
	  {								\
	    struct funcdesc_value fv = {				\
	      (void*)((SYMBOL) + *(REL)),				\
	      (LOAD).got_value						\
	    };								\
	    *(struct funcdesc_value volatile *)(REL) = fv;		\
	    break;							\
	  }								\
	default:							\
	  _dl_exit(1);							\
	}

/*
 * Transfer control to the user's application, once the dynamic loader
 * is done.  We return the address of the function's entry point to
 * _dl_boot, see boot1_arch.h.
 */
#define START()	do {							\
  struct elf_resolve *exec_mod = _dl_loaded_modules;			\
  dl_main_funcdesc->entry_point = _dl_elf_main;				\
  while (exec_mod->libtype != elf_executable)				\
    exec_mod = exec_mod->next;						\
  dl_main_funcdesc->got_value = exec_mod->loadaddr.got_value;		\
  return;								\
} while (0)
