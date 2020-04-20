LOCAL_PATH := $(call my-dir)


include $(CLEAR_VARS)


LOCAL_MODULE    := prboom


LOCAL_CFLAGS :=   -O2 -Werror=implicit-function-declaration   -DANDROID -DUSE_GLES  -DHAVE_CONFIG_H -g -Wall -Wextra -Wno-missing-field-initializers -Wwrite-strings  -Wbad-function-cast  -Wcast-qual -Wdeclaration-after-statement -Wpointer-arith  -Wno-unused -Wno-switch -Wno-sign-compare -Wno-pointer-sign -fsigned-char -fomit-frame-pointer -D_GNU_SOURCE=1 -D_REENTRANT

LOCAL_C_INCLUDES :=  $(LOCAL_PATH) $(TOP_DIR)/SDL/include $(TOP_DIR)/SDL_net/include $(TOP_DIR)/SDL_mixer  $(TOP_DIR)/SDL_image $(TOP_DIR)/openal/include $(TOP_DIR)/MobileTouchControls  $(TOP_DIR)/


#############################################################################
# CLIENT/SERVER
#############################################################################


COMMON_SRC = \
android-jni.cpp in_android.c \
 am_map.c       g_game.c           p_maputl.h       r_plane.h   \
 am_map.h       g_game.h           p_mobj.c         r_demo.c    r_segs.c    \
 hu_lib.c       lprintf.c          p_mobj.h         r_demo.h    r_segs.h    \
 hu_lib.h       lprintf.h          p_plats.c        r_sky.c	\
 d_deh.c        hu_stuff.c         m_argv.c         p_pspr.c    r_sky.h	    \
 d_deh.h        hu_stuff.h         m_argv.h         p_pspr.h    r_state.h   \
 d_englsh.h     i_joy.h            m_bbox.c         p_saveg.c   r_things.c  \
 d_event.h                         m_bbox.h         p_saveg.h   r_things.h  \
 d_items.c      i_network.h        m_cheat.c        p_setup.c   s_sound.c   \
 d_items.h      i_sound.h          m_cheat.h        p_setup.h   s_sound.h   \
 d_main.c       i_system.h         m_fixed.h        p_sight.c   sounds.c    \
 d_main.h       i_video.h          m_menu.c         p_spec.c    sounds.h    \
                info.c             m_menu.h         p_spec.h    st_lib.c    \
 d_net.h        info.h             m_misc.c         p_switch.c  st_lib.h    \
 d_player.h                        m_misc.h         p_telept.c  st_stuff.c  \
 m_random.c     p_tick.c           st_stuff.h       i_main.h    \
 d_think.h      m_random.h         p_tick.h         tables.c    \
 d_ticcmd.h     m_swap.h           p_user.c         tables.h     \
 doomdata.h     p_ceilng.c         p_user.h         v_video.c   \
 doomdef.c      p_doors.c          protocol.h       v_video.h   \
 doomdef.h      p_enemy.c          r_bsp.c          version.c   \
 doomstat.c     p_enemy.h          r_bsp.h          version.h   \
 doomstat.h     p_floor.c          r_data.c         w_wad.c	\
 doomtype.h     p_genlin.c         r_data.h         w_wad.h	\
 dstrings.c     p_inter.c          r_defs.h         wi_stuff.c  \
 dstrings.h     p_inter.h          r_draw.c         wi_stuff.h  \
 f_finale.c     p_lights.c         r_draw.h         z_bmalloc.c \
 f_finale.h     p_map.c            r_main.c         z_bmalloc.h \
 f_wipe.c       p_map.h            r_main.h         z_zone.c    \
 f_wipe.h       p_maputl.c         r_plane.c        z_zone.h	\
 md5.c          md5.h              p_checksum.h     p_checksum.c \
 r_patch.c      r_patch.h          r_fps.c          r_fps.h \
 r_filter.c     r_filter.h \
 e6y.c          e6y.h \
 i_pcsound.c    i_pcsound.h        r_screenmultiply.c r_screenmultiply.h \
 g_overflow.c   g_overflow.h       hu_tracers.c     hu_tracers.h \
 s_advsound.c   s_advsound.h       i_capture.c      i_capture.h \
 sc_man.c       sc_man.h \ 
 gl_map.c


NET_CLIENT_SRC = d_client.c
#USE_GL_SRC = 
USE_GL_SRC = \
  gl_opengl.c  gl_opengl.h \
  gl_detail.c  gl_intern.h  gl_main.c    gl_struct.h  gl_texture.c         gl_vertex.c \
  gl_wipe.c    gl_hires.c   gl_clipper.c gl_gamma.c   gl_missingtexture.c  gl_light.c \
  gl_hqresize.c gl_sky.c    gl_fbo.c     gl_shadow.c  gl_soft2gl.c         gl_preprocess.c \
  gl_drawinfo.c

#WAD_SRC = w_memcache.c
WAD_SRC = w_mmap.c

MUS2MID_SRC = memio.c memio.h mus2mid.c mus2mid.h	



LOCAL_SRC_FILES = $(COMMON_SRC)  $(NET_CLIENT_SRC) $(USE_GL_SRC) $(WAD_SRC) $(MUS2MID_SRC)

LOCAL_LDLIBS := -lGLESv1_CM -ldl -llog -lOpenSLES -lz 

LOCAL_LDLIBS += -fuse-ld=bfd

LOCAL_STATIC_LIBRARIES := s-setup nanogl pcsound  prboomsdl  doommusic textscreen SDL_net libjpeg 
LOCAL_SHARED_LIBRARIES := touchcontrols SDL SDL_mixer SDL_image 

include $(BUILD_SHARED_LIBRARY)






