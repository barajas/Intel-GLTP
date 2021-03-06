dnl
dnl Copyright (c) Serge Hallyn (2010)
dnl
dnl This program is free software;  you can redistribute it and/or modify
dnl it under the terms of the GNU General Public License as published by
dnl the Free Software Foundation; either version 2 of the License, or
dnl (at your option) any later version.
dnl
dnl This program is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY;  without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
dnl the GNU General Public License for more details.
dnl
dnl You should have received a copy of the GNU General Public License
dnl along with this program;  if not, write to the Free Software
dnl Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
dnl

AC_DEFUN([LTP_CHECK_SECUREBITS],[
	AC_CHECK_HEADERS(linux/securebits.h,[have_securebits=yes])
if test "x$have_securebits" != xyes; then
	have_securebits=no
fi
AC_SUBST(HAVE_SECUREBITS,$have_securebits)
])
