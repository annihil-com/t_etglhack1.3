// CREDITS:
//                        code: tesla
//      dlsym() hooking method: asciiascii
//              detour fn from: OGC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <zlib.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <zlib.h>
#include <time.h>
#include "hook.h"
#define T_VER "v1.3p"

#define X11_LIB "/usr/X11R6/lib/libX11.so.6"
//#define X11_LIB "/usr/lib/libX11.so.6"
// texture crc file
#define TEX_FILE "tesla_tex.crc\0"
// axis - textures crc32
#define AXIS1 0xf088bb4d
#define AXIS2 0xee6bc6ac
#define AXIS3 0x0e1639c3
#define AXIS4 0x7c867ce1
#define AXIS5 0x5ed79c76
#define AXIS6 0xb1d5182f
#define AXIS7 0xd1283a69
#define AXIS8 0xfba8ed6c
#define AXIS9 0xbfdc3e40
#define AXIS10 0x6aab7130
#define AXIS11 0xaf150c52
#define AXIS12 0x3a06352a
#define AXIS13 0xee6bc6ac
#define AXIS14 0x7568cb29
#define AXIS15 0x2c4a12c7
#define AXIS16 0x54b5ca6f
#define AXIS17 0x041fccd6
#define AXIS18 0xa7d09157
#define AXIS19 0x834bbd8a
#define AXIS20 0xa47642bd
#define AXIS21 0x847c176e
#define AXIS22 0xc0b2d5d8
#define AXIS23 0xb776d904
#define AXIS24 0xbf88f6dd
// allies textures - crc32
#define ALLIES1 0xc0b2d5d8
#define ALLIES2 0xb776d904
#define ALLIES3 0xbf88f6dd
#define ALLIES4 0x830b657a
#define ALLIES5 0x6e9fc473
#define ALLIES6 0xa0ce906d
#define ALLIES7 0x7512011f
#define ALLIES8 0xcfcc740d
#define ALLIES9 0x7d767da0
#define ALLIES10 0x58dec91d
#define ALLIES11 0x3cac280c
#define ALLIES12 0xe0a64ee4
#define ALLIES13 0x74cf14e6
#define ALLIES14 0x29def13e
#define ALLIES15 0x07967e31
#define ALLIES16 0x8b7180c2
#define ALLIES17 0xe018bac0
#define ALLIES18 0xb25f74f4
#define ALLIES19 0xce12113f
#define ALLIES20 0xce57570e
#define ALLIES21 0x041fccd6
// smoke crc
#define SMOKE1 0x74705124
#define SMOKE2 0x6579085d
#define SMOKE3 0xc1654e7d
#define SMOKE4 0x5497c4bd
#define SMOKE5 0x73689455
#define SMOKE6 0x9a728429
#define SMOKE7 0xdfa60635
#define SMOKE8 0xd0a7f49a
#define SMOKE9 0x2850edba
#define SMOKE10 0x5f5a0429
#define SMOKE11 0xb8cfc475
#define SMOKE12 0xe99cfc11
#define SMOKE13 0xef15ca9f
#define SMOKE14 0x339e300c
#define SMOKE15 0xd5d59de7
#define SMOKE16 0x814246de
#define SMOKE17 0x04754509
#define SMOKE18 0xb8e4cdd5
#define SMOKE19 0x2d23b9c4
#define SMOKE20 0xdd0ecfb5
#define SMOKE21 0x4c936e0c
#define SMOKE22 0xbf5bde6d
#define SMOKE23 0x00f17cd2
#define SMOKE24 0x6dc356eb
#define SMOKE25 0xe550bd06
#define SMOKE26 0x3517076e
#define SMOKE27 0x7ed90842
#define SMOKE28 0x8e7cd2c1
// fixed pee
#define NOPEE1 0x8cb0abba
#define NOPEE2 0xe4e0de4d
#define NOPEE3 0x059e9963
#define NOPEE4 0xbdc818e5
#define NOPEE5 0xaa521a00
#define NOPEE6 0x737edf10
#define NOPEE7 0x329c308a
#define NOPEE8 0x34c24c2c
#define NOPEE9 0x31db7e30
#define NOPEE10 0x7750e1a2
#define NOPEE11 0x9eea6b93
#define NOPEE12 0x8af162c2
#define NOPEE13 0xad390b44
#define NOPEE14 0x7217df1b
#define NOPEE15 0x29662bbc
#define NOPEE16 0x6a82e9ad
// sniper hack
#define SCOPEHACK 0xb4e473c9
// define how many menu entrys we will use
#define MENU_COUNT 15
// debug switch
#define T_DEBUG 0
// nothing now
GLfloat *v_pointer, BS;
// colored models
int r_value_teamA = 0x00;
int g_value_teamA = 0x00;
int b_value_teamA = 0xff;
GLubyte color_teamA[5000];
int r_value_teamB = 0xff;
int g_value_teamB = 0x00;
int b_value_teamB = 0x00;
GLubyte color_teamB[5000];
int r_value_teamP = 0xff;
int g_value_teamP = 0xff;
int b_value_teamP = 0x00;
int a_value_teamP = 0x20;
GLubyte color_teamP[5000];
// fonts shit
GLuint base;
Display *etwin;
// cheat switches
int initdone = 0;
int maluj = 0;
int wallhack_texture = 0;
int wallhack_mode = 0;
int wallhack_switch = 0;
int colored_switch = 0;
int null_switch = 0;
int pee_switch = 0;
int flat_switch = 0;
int line_switch = 0;
int smoke_switch = 0;
int nopee = 0;
int snip_t1 = 0;
int snip_t2 = 0;
int snip_tex = 0;
int scope_texture = 0;
int czyfonty = 0;
// menu here
typedef struct t_menu {
  int menu_position_nr;
  char menu_text[50];
  float m_x;
  float m_y;
  int m_r;
  int m_g;
  int m_b;
  int m_a;
} menus;
int curr_switch = 0;

static struct t_menu me[] = {
    {0, "* Re-Init Textures ", 200, 100, 0.0f, 1.0f, 0.0f, 1.0f},
    {1, "* WallHack          : ", 200, 114, 0.0f, 1.0f, 0.0f, 1.0f},
    {2, "* Colored Models    : ", 200, 128, 0.0f, 1.0f, 0.0f, 1.0f},
    {3, "* Pee World         : ", 200, 142, 0.0f, 1.0f, 0.0f, 1.0f},
    {4, "* Flat Models       : ", 200, 156, 0.0f, 1.0f, 0.0f, 1.0f},
    {5, "* Line Models       : ", 200, 170, 0.0f, 1.0f, 0.0f, 1.0f},
    {6, "- TeamA Color Red   : ", 200, 184, 0.0f, 1.0f, 0.0f, 1.0f},
    {7, "- TeamA Color Green : ", 200, 198, 0.0f, 1.0f, 0.0f, 1.0f},
    {8, "- TeamA Color Blue  : ", 200, 212, 0.0f, 1.0f, 0.0f, 1.0f},
    {9, "- TeamB Color Red   : ", 200, 226, 0.0f, 1.0f, 0.0f, 1.0f},
    {10, "- TeamB Color Green : ", 200, 240, 0.0f, 1.0f, 0.0f, 1.0f},
    {11, "- TeamB Color Blue  : ", 200, 254, 0.0f, 1.0f, 0.0f, 1.0f},
    {12, "* Activate Color", 200, 268, 0.0f, 1.0f, 0.0f, 1.0f},
    {13, "* CVOPS hack        : ", 200, 282, 0.0f, 1.0f, 0.0f, 1.0f},
    {14, "- Browse Texture    :  ", 200, 310, 0.0f, 1.0f, 0.0f, 1.0f}};

int menu_switches[MENU_COUNT];
int longest_entry = 0;
int cur_menu = 0;
float m_c_r = 0.0f;
float m_c_g = 0.0f;
float m_c_b = 0.2f;
int flash_mode = 0;
int flash_mode_r = 0;
int flash_mode_sw = 0;
// crc stuff
uLong crc1;
uLong crc_browse;
uLong crc_browsea;
int *dane_tex;
float *tex_image;
int texX;
int texY;
int texTot;

int texX_b;
int texY_b;
int texTot_b;

int texX_ba;
int texY_ba;
int texTot_ba;

// texture browser
int texture_browser = 0;
int last_texture_browser = 0;

// crosshair
GLuint hoho[3];
// textures
int axis_texz[2000];
int anal_axis = 0;

int allies_texz[2000];
int anal_allies = 0;

int pee_texz[100];
int anal_pee = 0;

int already_analized[5000];
int analized = 0;

int smoke_texz[200];
int anal_smoke = 0;

int scope_texz[200];
int anal_scope = 0;

GLuint texture2;
GLenum target2;
int whatisdrawn;
//#define DEBUG
// detour from ogc
void *detour_function(void *orig, void *det, int len, unsigned char *tramp) {
  if (len < 5) return 0;
  if (!tramp) {
    tramp = (unsigned char *)malloc(len + 5);
    memcpy(tramp, orig, len);
    tramp[len] = 0xE9;
    *((void **)(tramp + len + 1)) =
        (void *)((((uint)orig) + len) - (uint)(tramp + len + 5));
  }
  unprotect(GET_PAGE(orig), 4096);
  *((unsigned char *)orig) = 0xE9;
  *((void **)((uint)orig + 1)) = (void *)(((uint)det) - (((uint)orig) + 5));
  return tramp;
}

// Lib constructor - rip from asciiascii's etH-1.0
void __attribute__((constructor)) my_init(void) {
  // The only hard hook need
  if (orig_dlsym == NULL) {
    orig_dlsym = detour_function((void *)dlsym, &wrap_dlsym, 0x7, NULL);
    printf("detoutred dlsym\n");
  }
}

// The main hooker - rip from asciiascii's etH-1.0
void *wrap_dlsym(void *handle, const char *symbol) {
#ifdef DEBUG
  if (orig_dlsym == NULL) printf("ETH: wrap_dlsym: orig_dlsym was NULL");
  printf("ETH: wrap_dlsym: try to load function '%s' at library handle 0x%x\n",
         symbol, (unsigned int)handle);
#endif  // DEBUG
  void *result = orig_dlsym(handle, symbol);
  if (!strcmp(symbol, "glVertexPointer")) {
#ifdef DEBUG
    printf(
        "ETH: wrap_dlsym: glVertexPointer() found at 0x%x at lib handle 0x%x\n",
        (unsigned int)result, (unsigned int)handle);
#endif  // DEBUG
    org_glVertexPointer = result;
    return t_glVertexPointer;
  }

  if (!strcmp(symbol, "glBindTexture")) {
#ifdef DEBUG
    printf(
        "ETH: wrap_dlsym: glBindTexture() found at 0x%x at lib handle 0x%x\n",
        (unsigned int)result, (unsigned int)handle);
#endif  // DEBUG
    org_glBindTexture = result;
    return t_glBindTexture;
  }

  if (!strcmp(symbol, "glDrawElements")) {
#ifdef DEBUG
    printf(
        "ETH: wrap_dlsym: glDrawElements() found at 0x%x at lib handle 0x%x\n",
        (unsigned int)result, (unsigned int)handle);
#endif  // DEBUG
    org_glDrawElements = result;
    return t_glDrawElements;
  }

  if (!strcmp(symbol, "glEnable")) {
#ifdef DEBUG
    printf("ETH: wrap_dlsym: glEnable() found at 0x%x at lib handle 0x%x\n",
           (unsigned int)result, (unsigned int)handle);
#endif  // DEBUG
    org_glEnable = result;
    return t_glEnable;
  }

  if (!strcmp(symbol, "glXSwapBuffers")) {
#ifdef DEBUG
    printf(
        "ETH: wrap_dlsym: glXSwapBuffers() found at 0x%x at lib handle 0x%x\n",
        (unsigned int)result, (unsigned int)handle);
#endif  // DEBUG
    org_glXSwapBuffers = result;
    return t_glXSwapBuffers;
  }
  return result;
}

// crc32 texture counter
void t_crcTex(GLuint texture) {
  uLong crc2 = crc32(0L, Z_NULL, 0);
  int tex_x;
  int tex_y;
  int tex_total_size;
  dane_tex = malloc(2000);
  glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, dane_tex);
  tex_x = dane_tex[0];
  glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, dane_tex);
  tex_y = dane_tex[0];
  tex_total_size = (tex_x * tex_y) * 4 * sizeof(GLfloat);
  tex_image = malloc(tex_total_size);
  glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_FLOAT, tex_image);
  crc2 = crc32(crc2, (Bytef *)tex_image, tex_total_size);
  if (T_DEBUG == 1)
    printf("T>> Got: [tx:%d] [crc:%.08lx] [x:%d] [y:%d] [s:%d]\n", texture,
           crc2, tex_x, tex_y, tex_total_size);
  crc1 = crc2;
  texX = tex_x;
  texY = tex_x;
  texTot = tex_total_size;
  free(tex_image);
  free(dane_tex);
}

void t_saveTex_info() {
  FILE *f;

  if ((f = fopen(TEX_FILE, "a")) > 0) {
    fprintf(f, "no: %d - crc32: 0x%.8lx - size_x: %d - size_y: %d\n",
            texture_browser, crc_browsea, texX_ba, texY_ba);
    fclose(f);
    if (T_DEBUG == 1) printf("T>> Saved texture info to: %s\n", TEX_FILE);
  } else {
    if (T_DEBUG == 1) printf("T>> ERROR saving texture info: %s\n", TEX_FILE);
  }

  return;
}

////////////
// menu shit
// printf using GL + position (x,y)
void t_printfGLxy(float x, float y, float r, float g, float b, float a,
                  const char *fmt, ...) {
  va_list ap;
  char text[55];
  if (fmt == NULL) return;
  glColor4f(r, g, b, a);
  glRasterPos2f(x, y);
  va_start(ap, fmt);
  vsprintf(text, fmt, ap);
  va_end(ap);
  glPushAttrib(GL_LIST_BIT);
  glListBase(base - 31);
  glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
  glPopAttrib();
}

// create X11 std. font based fontmap
void t_loadFont(GLvoid) {
  XFontStruct *font;
  base = glGenLists(96);
  font = XLoadQueryFont(etwin, "fixed");
  if (font == NULL) {
    if (T_DEBUG == 1) printf("T>> NO \"fixed\" fonts ?!?!\n");
    exit(1);
  }
  glXUseXFont(font->fid, 31, 96, base);
  XFreeFont(etwin, font);
}

// drawbox at x,y,z with size h,w using mode and decide to use textures or not
void t_drawBox(GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height,
               GLuint mode, int draw_tex) {
  glBegin(mode);
  if (draw_tex == 1) glTexCoord2f(0.0f, 0.0f);
  glVertex3f(x, y, z);
  if (draw_tex == 1) glTexCoord2f(1.0f, 0.0f);
  glVertex3f(x + width, y, z);
  if (draw_tex == 1) glTexCoord2f(1.0f, 1.0f);
  glVertex3f(x + width, y + height, z);
  if (draw_tex == 1) glTexCoord2f(0.0f, 1.0f);
  glVertex3f(x, y + height, z);
  glEnd();
}

// draw menu entrys
void t_drawMenuEnt(int m_no, int hack_switch) {
  char *switch_value[4] = {"OFF", "ON",
                           "TEXTURE NUMBER",  // not implemented yet
                           "TEXTURE CRC32"};
  char menu_total_text[55];
  float r;
  float g;
  float b;
  float a;

  bzero(menu_total_text, sizeof(menu_total_text));
  sprintf(menu_total_text, "%s%s", me[m_no].menu_text,
          switch_value[hack_switch]);

  if (m_no == 0 || m_no == 12) {
    bzero(menu_total_text, sizeof(menu_total_text));
    sprintf(menu_total_text, "%s", me[m_no].menu_text);
  }

  if (m_no == 6) {
    bzero(menu_total_text, sizeof(menu_total_text));
    sprintf(menu_total_text, "%s0x%.2x", me[m_no].menu_text, r_value_teamA);
  }
  if (m_no == 7) {
    bzero(menu_total_text, sizeof(menu_total_text));
    sprintf(menu_total_text, "%s0x%.2x", me[m_no].menu_text, g_value_teamA);
  }
  if (m_no == 8) {
    bzero(menu_total_text, sizeof(menu_total_text));
    sprintf(menu_total_text, "%s0x%.2x", me[m_no].menu_text, b_value_teamA);
  }
  if (m_no == 9) {
    bzero(menu_total_text, sizeof(menu_total_text));
    sprintf(menu_total_text, "%s0x%.2x", me[m_no].menu_text, r_value_teamB);
  }
  if (m_no == 10) {
    bzero(menu_total_text, sizeof(menu_total_text));
    sprintf(menu_total_text, "%s0x%.2x", me[m_no].menu_text, g_value_teamB);
  }

  if (m_no == 11) {
    bzero(menu_total_text, sizeof(menu_total_text));
    sprintf(menu_total_text, "%s0x%.2x", me[m_no].menu_text, b_value_teamB);
  }

  if (m_no == 14) {
    bzero(menu_total_text, sizeof(menu_total_text));
    sprintf(menu_total_text, "%s %d", me[m_no].menu_text, texture_browser);
  }

  if (longest_entry < strlen(menu_total_text))
    longest_entry = strlen(menu_total_text);
  if (cur_menu == m_no) {
    r = 0.0f;
    g = 0.0f;
    b = 1.0f;
    a = 1.0f;
  } else {
    r = me[m_no].m_r;
    g = me[m_no].m_g;
    b = me[m_no].m_b;
    a = me[m_no].m_a;
  }

  if (cur_menu != m_no)
    t_printfGLxy(me[m_no].m_x + 2, me[m_no].m_y + 2, 0, 0, 0, 1,
                 menu_total_text);
  t_printfGLxy(me[m_no].m_x, me[m_no].m_y, r, g, b, a, menu_total_text);
}

void t_updatehackswitchez() {
  wallhack_mode = menu_switches[0] + 2;
  wallhack_switch = menu_switches[1];
  colored_switch = menu_switches[2];
  pee_switch = menu_switches[3];
  flat_switch = menu_switches[4];
  line_switch = menu_switches[5];
  smoke_switch = menu_switches[13];
}

// main menu drawing function
void t_drawMenu() {
  glPushMatrix();
  glLoadIdentity();
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_DEPTH_TEST);
  t_updatehackswitchez();
  wallhack_mode = menu_switches[0] + 2;
  wallhack_switch = menu_switches[1];
  colored_switch = menu_switches[2];
  pee_switch = menu_switches[3];
  flat_switch = menu_switches[4];
  line_switch = menu_switches[5];
  smoke_switch = menu_switches[13];
  glColor4f(0.1f, 0.1f, 0.1f, 1.0f);
  t_drawBox(me[0].m_x - 1 - 2.0f, 76 - 12.0f - 2, -1.0f, 405, 254, GL_QUADS, 0);

  glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
  t_drawBox(me[0].m_x - 1.0f, me[0].m_y - 12.0f, -1.0f,
            (float)longest_entry * 6 + 4,
            me[MENU_COUNT - 1].m_y - me[0].m_y + 16, GL_QUADS, 0);
  // texture browser

  t_drawBox(400, 76 - 12.0f, -1.0f, 200, 250, GL_QUADS, 0);
  glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
  t_drawBox(402, 278 - 12.0f, -1.0f, 196, 46, GL_QUADS, 0);

  org_glEnable(GL_TEXTURE_2D);
  org_glBindTexture(GL_TEXTURE_2D, texture_browser);
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  t_drawBox(402, 78 - 12.0f, -1.0f, 196, 196, GL_QUADS, 1);
  if (last_texture_browser != texture_browser) {
    // push texture values
    texX_b = texX;
    texY_b = texY;
    texTot_b = texTot;
    crc_browse = crc1;

    t_crcTex(texture_browser);

    texX_ba = texX;
    texY_ba = texY;
    texTot_ba = texTot;
    crc_browsea = crc1;

    // pop texture values
    texX = texX_b;
    texY = texY_b;
    texTot = texTot_b;
    crc1 = crc_browse;
    last_texture_browser = texture_browser;
  }
  glDisable(GL_TEXTURE_2D);

  t_printfGLxy(402, 278, 1.0f, 1.0f, 0.0f, 1.0f, "Tex. number: %d",
               texture_browser);
  t_printfGLxy(402, 278 + 14, 1.0f, 1.0f, 0.0f, 1.0f, "Tex. crc32: 0x%.8lx",
               crc_browsea);
  t_printfGLxy(402, 278 + 14 + 14, 1.0f, 1.0f, 0.0f, 1.0f,
               "Tex. size (XxY): %d x %d", texX_ba, texY_ba);

  glColor4f(m_c_r, m_c_g, m_c_b, 1.0f);
  t_drawBox(me[cur_menu].m_x - 1.0f, me[cur_menu].m_y - 12.0f, -1.0f,
            (float)longest_entry * 6 + 4, 16, GL_QUADS, 0);

  t_drawBox(200 - 1.0f, 76 - 12.0f, -1.0f, (float)longest_entry * 6 + 4, 16,
            GL_QUADS, 0);

  t_printfGLxy(200, 76, 1.0f, 1.0f, 0.0f, 1.0f, ": TESLA ETGLHackII %s ",
               T_VER);
  t_drawMenuEnt(0, null_switch);
  t_drawMenuEnt(1, wallhack_switch);
  t_drawMenuEnt(2, colored_switch);
  t_drawMenuEnt(3, pee_switch);
  t_drawMenuEnt(4, flat_switch);
  t_drawMenuEnt(5, line_switch);
  t_drawMenuEnt(6, null_switch);
  t_drawMenuEnt(7, null_switch);
  t_drawMenuEnt(8, null_switch);
  t_drawMenuEnt(9, null_switch);
  t_drawMenuEnt(10, null_switch);
  t_drawMenuEnt(11, null_switch);
  t_drawMenuEnt(12, null_switch);
  t_drawMenuEnt(13, smoke_switch);
  t_drawMenuEnt(14, null_switch);

  org_glEnable(GL_DEPTH_TEST);
  org_glEnable(GL_TEXTURE_2D);
  org_glBindTexture(target2, texture2);

  glPopMatrix();
}

// crosshair ripped from n7 + litle change
void t_drawCross() {
  glPushMatrix();
  glLoadIdentity();
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_DEPTH_TEST);
  glGetIntegerv(GL_VIEWPORT, hoho);
  glLineWidth(3);
  glBegin(GL_LINES);
  glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
  glVertex2i(hoho[2] / 2, (hoho[3] / 2) - 4);
  glVertex2i(hoho[2] / 2, (hoho[3] / 2) - 0);

  glVertex2i(hoho[2] / 2, (hoho[3] / 2) - 0);
  glVertex2i(hoho[2] / 2, (hoho[3] / 2) + 5);
  glVertex2i((hoho[2] / 2) - 4, hoho[3] / 2);
  glVertex2i((hoho[2] / 2) - 0, hoho[3] / 2);

  glVertex2i((hoho[2] / 2) - 0, hoho[3] / 2);
  glVertex2i((hoho[2] / 2) + 5, hoho[3] / 2);
  glEnd();

  glLineWidth(1);
  glBegin(GL_LINES);
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  glVertex2i(hoho[2] / 2, (hoho[3] / 2) - 3);
  glVertex2i(hoho[2] / 2, (hoho[3] / 2) - 0);

  glVertex2i(hoho[2] / 2, (hoho[3] / 2) - 0);
  glVertex2i(hoho[2] / 2, (hoho[3] / 2) + 4);
  glVertex2i((hoho[2] / 2) - 3, hoho[3] / 2);
  glVertex2i((hoho[2] / 2) - 0, hoho[3] / 2);

  glVertex2i((hoho[2] / 2) - 0, hoho[3] / 2);
  glVertex2i((hoho[2] / 2) + 4, hoho[3] / 2);
  glEnd();

  org_glEnable(GL_TEXTURE_2D);
  org_glEnable(GL_DEPTH_TEST);
  glPopMatrix();
}

// create and load color arrays
void t_loadColor() {
  int i;

  org_glEnable(GL_COLOR_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

  for (i = 0; i <= 4998; i = i + 4) {
    color_teamA[i] = r_value_teamA;
    color_teamA[i + 1] = g_value_teamA;
    color_teamA[i + 2] = b_value_teamA;
    color_teamA[i + 3] = 0xff;

    color_teamB[i] = r_value_teamB;
    color_teamB[i + 1] = g_value_teamB;
    color_teamB[i + 2] = b_value_teamB;
    color_teamB[i + 3] = 0xff;

    color_teamP[i] = r_value_teamP;
    color_teamP[i + 1] = g_value_teamP;
    color_teamP[i + 2] = b_value_teamP;
    color_teamP[i + 3] = a_value_teamP;
  }
}

// short version of return(XLooku...
KeySym t_getKey(XEvent *event_return) {
  return (XLookupKeysym(&event_return->xkey, 0));
}

// Init XNextEvent here
void t_initCheat() {
  org_XNextEvent = (int (*)(Display *display, XEvent *event_return))orig_dlsym(
      RTLD_NEXT, "XNextEvent");
  initdone = 1;
}

// moved here to make it more mobile ex: shortkeys
void t_switch() {
  if (menu_switches[cur_menu] == 0) {
    menu_switches[cur_menu] = 1;
  } else {
    menu_switches[cur_menu] = 0;
  }
}

// reinit textures , needed when mode changes
void t_reinitTex() {
  bzero(axis_texz, 2000);
  anal_axis = 0;
  bzero(allies_texz, 2000);
  anal_allies = 0;
  bzero(pee_texz, 100);
  anal_pee = 0;

  bzero(smoke_texz, 2000);
  anal_smoke = 0;

  bzero(already_analized, 5000);
  analized = 0;
  snip_t1 = 0;
  snip_t2 = 0;
  snip_tex = 0;
  scope_texture = 0;
  anal_scope = 0;
  bzero(scope_texz, sizeof(200));
}

// check what are we going to draw
void t_ismodelTexture(GLuint texture) {
  int i;
  whatisdrawn = 0;
  nopee = 0;
  snip_tex = 0;
  wallhack_texture = 0;
  scope_texture = 0;

  // check for scope/hud
  for (i = 0; i < (anal_scope + 1); i++) {
    if (scope_texz[i] == texture) {
      scope_texture = 1;
      return;
    }
  }
  // check for scope/hud
  if (snip_t1 > 0)
    if (snip_t1 == texture) {
      snip_tex = 1;
      return;
    }
  // check for scope/hud
  if (snip_t2 > 0)
    if (snip_t2 == texture) {
      snip_tex = 1;
      return;
    }
  // check fixed pee
  for (i = 0; i < (anal_pee + 1); i++) {
    if (pee_texz[i] == texture) {
      nopee = 1;
      return;
    }
  }

  // check for cached axis
  for (i = 0; i < (anal_axis + 1); i++) {
    if (axis_texz[i] == texture) {
      wallhack_texture = 1;
      whatisdrawn = 1;
      return;
    }
  }
  // and for allies
  for (i = 0; i < (anal_allies + 1); i++) {
    if (allies_texz[i] == texture) {
      wallhack_texture = 1;
      whatisdrawn = 2;
      return;
    }
  }
  // and smoke
  for (i = 0; i < (anal_smoke + 1); i++) {
    if (smoke_texz[i] == texture) {
      wallhack_texture = 0;
      whatisdrawn = 3;
      return;
    }
  }

  // check global textures cache
  for (i = 0; i < (analized + 1); i++) {
    if (texture == already_analized[i]) {
      wallhack_texture = 0;
      return;
    }
  }
  already_analized[analized] = texture;
  analized++;

  t_crcTex(texture);

  // detect scope/hud textures
  if (crc1 == (uLong)SCOPEHACK) {
    scope_texz[anal_scope] = texture;
    anal_scope++;
    if (T_DEBUG == 1) printf("T>> FOUND SCOPE/HUD 0x%.08lx\n", crc1);
    scope_texture = 1;
    return;
  }

  // detect scope/bin textures
  if (crc1 == (uLong)NOPEE15) {
    snip_t1 = texture;
    snip_tex = 1;
    if (T_DEBUG == 1) printf("T>> FOUND SCOPE/BIN 0x%.08lx\n", crc1);
    return;
  }
  if (crc1 == (uLong)NOPEE16) {
    snip_t2 = texture;
    snip_tex = 2;
    if (T_DEBUG == 1) printf("T>> FOUND SCOPE/BIN 0x%.08lx\n", crc1);
    return;
  }

  // detect no-pee textures

  if (crc1 == (uLong)NOPEE1 || crc1 == (uLong)NOPEE2 || crc1 == (uLong)NOPEE3 ||
      crc1 == (uLong)NOPEE4 || crc1 == (uLong)NOPEE5 || crc1 == (uLong)NOPEE6 ||
      crc1 == (uLong)NOPEE7 || crc1 == (uLong)NOPEE8 || crc1 == (uLong)NOPEE9 ||
      crc1 == (uLong)NOPEE10 || crc1 == (uLong)NOPEE11 ||
      crc1 == (uLong)NOPEE12 || crc1 == (uLong)NOPEE13 ||
      crc1 == (uLong)NOPEE14) {
    if (T_DEBUG == 1) printf("T>> FOUND PEE 0x%.08lx\n", crc1);
    pee_texz[anal_pee] = texture;
    anal_pee++;
    nopee = 1;
    return;
  }
  // detect AXIS textures

  if (crc1 == (uLong)AXIS1 || crc1 == (uLong)AXIS2 || crc1 == (uLong)AXIS3 ||
      crc1 == (uLong)AXIS4 || crc1 == (uLong)AXIS5 || crc1 == (uLong)AXIS6 ||
      crc1 == (uLong)AXIS7 || crc1 == (uLong)AXIS8 || crc1 == (uLong)AXIS9 ||
      crc1 == (uLong)AXIS10 || crc1 == (uLong)AXIS11 || crc1 == (uLong)AXIS12 ||
      crc1 == (uLong)AXIS13 || crc1 == (uLong)AXIS14 || crc1 == (uLong)AXIS15 ||
      crc1 == (uLong)AXIS16 || crc1 == (uLong)AXIS17 || crc1 == (uLong)AXIS18 ||
      crc1 == (uLong)AXIS19 || crc1 == (uLong)AXIS20 || crc1 == (uLong)AXIS21 ||
      crc1 == (uLong)AXIS22 || crc1 == (uLong)AXIS23) {
    if (T_DEBUG == 1) printf("T>> FOUND AXIS 0x%.08lx\n", crc1);
    axis_texz[anal_axis] = texture;
    anal_axis++;
    wallhack_texture = 1;
    whatisdrawn = 1;
    return;
  }
  // detect ALLIES textures
  if (crc1 == (uLong)ALLIES1 || crc1 == (uLong)ALLIES2 ||
      crc1 == (uLong)ALLIES3 || crc1 == (uLong)ALLIES4 ||
      crc1 == (uLong)ALLIES5 || crc1 == (uLong)ALLIES6 ||
      crc1 == (uLong)ALLIES7 || crc1 == (uLong)ALLIES8 ||
      crc1 == (uLong)ALLIES9 || crc1 == (uLong)ALLIES10 ||
      crc1 == (uLong)ALLIES11 || crc1 == (uLong)ALLIES12 ||
      crc1 == (uLong)ALLIES13 || crc1 == (uLong)ALLIES14 ||
      crc1 == (uLong)ALLIES15 || crc1 == (uLong)ALLIES16 ||
      crc1 == (uLong)ALLIES17 || crc1 == (uLong)ALLIES18 ||
      crc1 == (uLong)ALLIES19 || crc1 == (uLong)ALLIES20 ||
      crc1 == (uLong)ALLIES21) {
    if (T_DEBUG == 1) printf("T>> FOUND ALLIES 0x%.08lx\n", crc1);
    allies_texz[anal_allies] = texture;
    anal_allies++;
    wallhack_texture = 1;
    whatisdrawn = 2;
    return;
  }

  if (crc1 == (uLong)SMOKE1 || crc1 == (uLong)SMOKE2 || crc1 == (uLong)SMOKE3 ||
      crc1 == (uLong)SMOKE4 || crc1 == (uLong)SMOKE5 || crc1 == (uLong)SMOKE6 ||
      crc1 == (uLong)SMOKE7 || crc1 == (uLong)SMOKE8 || crc1 == (uLong)SMOKE9 ||
      crc1 == (uLong)SMOKE10 || crc1 == (uLong)SMOKE11 ||
      crc1 == (uLong)SMOKE12 || crc1 == (uLong)SMOKE13 ||
      crc1 == (uLong)SMOKE14 || crc1 == (uLong)SMOKE15 ||
      crc1 == (uLong)SMOKE16 || crc1 == (uLong)SMOKE17 ||
      crc1 == (uLong)SMOKE18 || crc1 == (uLong)SMOKE19 ||
      crc1 == (uLong)SMOKE20 || crc1 == (uLong)SMOKE21 ||
      crc1 == (uLong)SMOKE22 || crc1 == (uLong)SMOKE23 ||
      crc1 == (uLong)SMOKE24 || crc1 == (uLong)SMOKE25 ||
      crc1 == (uLong)SMOKE26 || crc1 == (uLong)SMOKE27 ||
      crc1 == (uLong)SMOKE28) {
    if (T_DEBUG == 1) printf("T>> FOUND SMOKE 0x%.08lx\n", crc1);
    smoke_texz[anal_smoke] = texture;
    anal_smoke++;
    wallhack_texture = 0;
    whatisdrawn = 3;
    return;
  }
}

// for sniper hack, thanks N7
void t_glVertexPointer(GLint size, GLenum type, GLsizei stride,
                       const GLvoid *pointer) {
  GLfloat *x;
  if (smoke_switch == 1) {
    (GLfloat *)v_pointer = (GLfloat *)pointer;
    x = (GLfloat *)v_pointer + 0;
    BS = *x;
  }
  org_glVertexPointer(size, type, stride, pointer);
}

// my glBindTexture()
void t_glBindTexture(GLenum target, GLuint texture) {
  if (initdone == 0) t_initCheat();  // init is verrry important here
  target2 = target;
  texture2 = texture;
  org_glBindTexture(target, texture);  // call original function
}

// my glDrawElements
void t_glDrawElements(GLenum mode, GLsizei count, GLenum type,
                      const GLvoid *indices) {
  if (initdone == 0) t_initCheat();  // init is verrry important here

  t_ismodelTexture(texture2);
  // flat models
  if (flat_switch == 1) {
    if (wallhack_texture == 1) {
      glDisable(GL_TEXTURE_2D);
    } else {
      org_glEnable(GL_TEXTURE_2D);
    }
  }
  // colored models
  if (colored_switch == 1)
    if (wallhack_texture == 1) {
      if (whatisdrawn == 1)
        glColorPointer(4, GL_UNSIGNED_BYTE, 0, &color_teamB);
      if (whatisdrawn == 2)
        glColorPointer(4, GL_UNSIGNED_BYTE, 0, &color_teamA);
    }

  // pee world
  if (pee_switch == 1)
    if (wallhack_texture == 0 && texture2 > 100 && nopee == 0) {  // fixed pee
      glColorPointer(4, GL_UNSIGNED_BYTE, 0, &color_teamP);
    }
  // line models
  if (line_switch == 1)
    if (wallhack_texture == 1) {
      mode = GL_LINES;
    }
  // wallhack
  if (wallhack_switch == 1) {
    if (wallhack_texture == 1) {
      glDisable(GL_DEPTH_TEST);
    } else {
      org_glEnable(GL_DEPTH_TEST);
    }
  }
  // call original function if not drawing smoke or smtg
  if (smoke_switch == 1) {
    if (whatisdrawn == 3 || snip_tex != 0 ||
        (scope_texture == 1 && count == 12 && BS < 1))  // nosmoke+scope/binhack
      return;
    else
      org_glDrawElements(mode, count, type, indices);
  } else {
    org_glDrawElements(mode, count, type, indices);
  }
}

// my XNextEvent() used to grab keys
int t_XNextEvent(Display *display, XEvent *event_return) {
  int ret_value;
  etwin = display;
  ret_value = org_XNextEvent(display, event_return);
  if ((event_return->type) == 2) {
    if (t_getKey(event_return) == XK_Home) {
      t_loadFont();
      t_loadColor();
      if (maluj == 0) {
        maluj = 1;
      } else {
        maluj = 0;
      }
    }
    if (t_getKey(event_return) == XK_Up && maluj == 1) {
      cur_menu--;
      if (cur_menu < 0) cur_menu = MENU_COUNT - 1;
    }

    if (t_getKey(event_return) == XK_Down && maluj == 1) {
      cur_menu++;
      if (cur_menu > MENU_COUNT - 1) cur_menu = 0;
    }

    if (t_getKey(event_return) == XK_Left && maluj == 1) {
      if (cur_menu == 6) {
        r_value_teamA--;
        if (r_value_teamA < 0) r_value_teamA = 0;
      }
      if (cur_menu == 7) {
        g_value_teamA--;
        if (g_value_teamA < 0) g_value_teamA = 0;
      }
      if (cur_menu == 8) {
        b_value_teamA--;
        if (b_value_teamA < 0) b_value_teamA = 0;
      }

      if (cur_menu == 9) {
        r_value_teamB--;
        if (r_value_teamB < 0) r_value_teamB = 0;
      }
      if (cur_menu == 10) {
        g_value_teamB--;
        if (g_value_teamB < 0) g_value_teamB = 0;
      }
      if (cur_menu == 11) {
        b_value_teamB--;
        if (b_value_teamB < 0) b_value_teamB = 0;
      }

      if (cur_menu == 14) {
        texture_browser--;
        if (texture_browser < 0) texture_browser = 2000;
      }
    }

    if (t_getKey(event_return) == XK_Right && maluj == 1) {
      if (cur_menu == 6) {
        r_value_teamA++;
        if (r_value_teamA > 0xff) r_value_teamA = 0xff;
      }
      if (cur_menu == 7) {
        g_value_teamA++;
        if (g_value_teamA > 0xff) g_value_teamA = 0xff;
      }
      if (cur_menu == 8) {
        b_value_teamA++;
        if (b_value_teamA > 0xff) b_value_teamA = 0xff;
      }

      if (cur_menu == 9) {
        r_value_teamB++;
        if (r_value_teamB > 0xff) r_value_teamB = 0xff;
      }
      if (cur_menu == 10) {
        g_value_teamB++;
        if (g_value_teamB > 0xff) g_value_teamB = 0xff;
      }
      if (cur_menu == 11) {
        b_value_teamB++;
        if (b_value_teamB > 0xff) b_value_teamB = 0xff;
      }

      if (cur_menu == 14) {
        texture_browser++;
        if (texture_browser > 2000) texture_browser = 0;
      }
    }

    if (t_getKey(event_return) == XK_Return && maluj == 1) {
      if (cur_menu == 0) t_reinitTex();
      if (cur_menu == 12) t_loadColor();
      if (cur_menu == 14) t_saveTex_info();
      t_switch();
    }
  }
  return ret_value;
}

// my glEnable() used to draw menu and crosshair
void t_glEnable(GLenum cap) {
  if (initdone == 0) t_initCheat();
  org_glEnable(cap);
}

// call to mine function as orig one
int XNextEvent(Display *display, XEvent *event_return) {
  return (t_XNextEvent(display, event_return));
}

// glXSwapBuffers() used to draw menu etc - one per frame :]
void t_glXSwapBuffers(Display *dpy, GLXDrawable drawable) {
  if (initdone == 0) t_initCheat();  // init is verrry important here
  if (czyfonty == 0) {
    t_loadFont();
    czyfonty = 1;
  }
  if (maluj == 1) {
    flash_mode_r++;
    if (flash_mode_r == 4) flash_mode_r = 0;
    if (flash_mode == 0) {
      m_c_r = m_c_r + 0.01f;
      if (flash_mode_r == 3) m_c_g = m_c_g + 0.01f;
    } else {
      m_c_r = m_c_r - 0.01f;
      if (flash_mode_r == 3) m_c_g = m_c_g - 0.01f;
    }
    if (m_c_g < 0.2f) m_c_g = 0.2f;
    if (m_c_g > 0.7f) m_c_g = 0.7f;
    if (m_c_r > 1.0f) {
      m_c_r = 1.0f;
      flash_mode = 1;
    }
    if (m_c_r < 0.2f) {
      m_c_r = 0.2f;
      flash_mode = 0;
    }
    t_drawMenu();
  }
  // crosshair here
  if (pee_switch == 1) t_drawCross();
  org_glXSwapBuffers(dpy, drawable);
}
