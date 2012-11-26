/*
** RopGadget - Release v3.4.2
** Jonathan Salwan - http://twitter.com/JonathanSalwan
** http://shell-storm.org
** 2012-11-11
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "ropgadget.h"

void set_all_flag(void)
{
  flag_elfheader          = 0;
  flag_progheader         = 0;
  flag_sectheader         = 0;
  flag_symtab             = 0;
  flag_g                  = 0;
  syntaxcode              = SYN_PYTHON;  /* python syntax by default */
  limitmode.flag          = 0;
  limitmode.value         = -1; /* default unlimited */
  opcode_mode.flag        = 0;
  stringmode.flag         = 0;
  bind_mode.flag          = 0;
  bind_mode.port          = 1337; /* default port */
  asm_mode.flag           = 0;
  mapmode.flag            = 0;
  filter_mode.flag        = 0;
  filter_linked           = NULL;
  only_mode.flag          = 0;
  only_linked             = NULL;
  opcode_mode.flag        = 0;
  importsc_mode.flag      = 0;
  syntaxins.type          = INTEL; /* Display with INTEL syntax by default */
}

unsigned char *save_bin_in_memory(char *file)
{
  int fd;
  unsigned char *data;
  struct stat filestat;

  fd = xopen(file, O_RDONLY, 0644);
  stat(file, &filestat);
  filemode.size = filestat.st_size;
  filemode.file = file;
  data = xmalloc(filemode.size * sizeof(char));
  read(fd, data, filemode.size);
  pMapElf = xmmap(0, filemode.size, PROT_READ, MAP_SHARED, fd, 0);
  filemode.data = data;
  pElf_Header = (Elf32_Ehdr *)data;
  pElf32_Shdr = (Elf32_Shdr *)((char *)data + pElf_Header->e_shoff);
  pElf32_Phdr = (Elf32_Phdr *)((char *)data + pElf_Header->e_phoff);
  close(fd);

  return (data);
}
