// GPL License - see http://opensource.org/licenses/gpl-license.php
// Copyright 2005 eth team - don't forget to credits us

#ifndef HOOK_H
#define HOOK_H

#define __USE_GNU
#define _GNU_SOURCE
#include <dlfcn.h>
#include <sys/mman.h>

// Detour function taken from ogc3-q3
#define unprotect(addr,len) (mprotect(addr,len,PROT_READ|PROT_WRITE|PROT_EXEC))
#define reprotect(addr,len) (mprotect(addr,len,PROT_READ|PROT_EXEC))
#define GET_PAGE(a) ((void*)(((unsigned long)a)&0xfffff000))
			
void *wrap_dlsym(void *handle, const char *symbol);
void *(*orig_dlsym) (void *handle, const char *symbol);   
void *detour_function(void *, void *, int, unsigned char *);

void t_glBindTexture(GLenum target,GLuint texture);                                                   
void t_glDrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices);                
void t_glEnable(GLenum cap);                                                                          
void t_glVertexPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);               
void t_glXSwapBuffers (Display *dpy, GLXDrawable drawable );   

void (*org_glBindTexture)(GLenum target,GLuint texture);
void (*org_glDrawElements)(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices);
void (*org_glEnable)(GLenum cap);
void (*org_glVertexPointer)(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
int (*org_XNextEvent) (Display *display, XEvent *event_return);
void (*org_glXSwapBuffers) (Display *dpy, GLXDrawable drawable );


#endif // HOOK_H
