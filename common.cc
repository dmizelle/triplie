/*
 *  Copyright (C) Gorgi Kosev a.k.a. Spion, John Peterson.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
#include "common.h"

u8 verb = 1;

void log(const char* f, ...) {
	const int len = 0xfff;
	char buf[len];
	va_list l;
	va_start(l, f);
	vsnprintf(buf, len, f, l);
	va_end(l);
	fprintf(stderr, "\033[1;30m%s\033[0m %s", time_hm().c_str(), buf);
}
void log(const char *f, va_list &l_) {
	const int len = 0xfff;
	char buf[len];	
	va_list *l = &l_;
	vsnprintf(buf, len, f, *l);
	fprintf(stderr, "\033[1;30m%s\033[0m %s", time_hm().c_str(), buf);
}
void log1(const char* f, ...) {
	if (verb < 1) return;
	va_list l;
	va_start(l, f);
	log(f, l);
	va_end(l);
}
void log2(const char* f, ...) {
	if (verb < 2) return;
	va_list l;
	va_start(l, f);
	log(f, l);
	va_end(l);
}
string format(const char* f, ...) {
	const int len = 0xfff;
	char buf[len];
	va_list l;
	va_start(l, f);
	vsnprintf(buf, len, f, l);
	va_end(l);
	return string(buf);
}

double seconds() {
    timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec*1000.0)+(tv.tv_usec/1000.0);
}
string time_hm() {
	time_t t = time(0);
	const u8 len = 0xff;
	char buf[len];
	strftime(buf, len, "%H:%M", localtime(&t));
	return string(buf);
}

string format_bytes(s64 bytes) {
	string sfx[] = {"B","kiB","MiB","GiB","TiB","PiB","EiB","ZiB","YiB"};
	u32 i;
	for (i = 0; bytes / 1024 > 0 && i < 8; i++, bytes /= 1024) {}
	return format("%lld %s", bytes, sfx[i].c_str());
}
off_t fsize(string f) {
	struct stat filestatus;
	stat(f.c_str(), &filestatus);
	return filestatus.st_size;
}