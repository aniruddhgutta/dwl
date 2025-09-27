/* Taken from https://github.com/djpohly/dwl/issues/466 */
#define COLOR(hex)    { ((hex >> 24) & 0xFF) / 255.0f, \
                        ((hex >> 16) & 0xFF) / 255.0f, \
                        ((hex >> 8) & 0xFF) / 255.0f, \
                        (hex & 0xFF) / 255.0f }
/* appearance */
static const int sloppyfocus               = 1;  /* focus follows mouse */
static const int bypass_surface_visibility = 0;  /* 1 means idle inhibitors will disable idle tracking even if it's surface isn't visible  */
static const int smartgaps                 = 0;  /* 1 means no outer gap when there is only one window */
static int gaps                            = 1;  /* 1 means gaps between windows are added */
static const unsigned int gappx            = 10; /* gap pixel between windows */
static const unsigned int borderpx         = 1;  /* border pixel of windows */
static const char *colors_dir              = {"/home/vye/.cache/wal/colors.h"}; /* path to color definitions */
static const int showbar                   = 1; /* 0 means no bar */
static const int topbar                    = 1; /* 0 means bottom bar */
static const char *fonts[]                 = {"monospace:size=10"};
static const float rootcolor[]             = COLOR(0x000000ff);
/* This conforms to the xdg-protocol. Set the alpha to zero to restore the old behavior */
static const float fullscreen_bg[]         = {0.0f, 0.0f, 0.0f, 1.0f}; /* You can also use glsl colors */
static const char *cursor_theme            = NULL;
static const char cursor_size[]            = "16"; /* Make sure it's a valid integer, otherwise things will break */
static uint32_t colors[][3]                = {
	/*               fg          bg          border    */
	[SchemeNorm] = { 0xbbbbbbff, 0x222222ff, 0x444444ff },
	[SchemeSel]  = { 0xeeeeeeff, 0x005577ff, 0x005577ff },
	[SchemeUrg]  = { 0,          0,          0x770000ff },
};

/* tagging */
static char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

/* logging */
static int log_level = WLR_ERROR;

/* passthrough */
static int passthrough = 0;

/* window resizing */
/* resize_corner:
 * 0: top-left
 * 1: top-right
 * 2: bottom-left
 * 3: bottom-right
 * 4: closest to the cursor
 */
static const int resize_corner = 4;
static const int warp_cursor = 1;	/* 1: warp to corner, 0: don’t warp */
static const int lock_cursor = 0;	/* 1: lock cursor, 0: don't lock */

/* setupenv */
static const Env envs[] = {
	/* variable			value */
	{ "XDG_CURRENT_DESKTOP", "wlroots" },
    { "ELECTRON_OZONE_PLATFORM_HINT", "wayland" },
};

/* autostart */
static const char *const autostart[] = {
    "dbus-update-activation-environment", "WAYLAND_DISPLAY", "XDG_CURRENT_DESKTOP", NULL,
    "pipewire", NULL,
    "mpd", NULL,
    "mpd-notify", NULL,
    "theme", "-r", NULL,
    "foot", "--server", NULL,
    "wl-clip-persist", "--clipboard", "regular", NULL,
    "wl-paste", "--type", "text", "--watch", "cliphist", "store", NULL,
    "wl-paste", "--type", "image", "--watch", "cliphist", "store", NULL,
    NULL /* terminate */
};

/* AT LEAST ONE rule must exist. Define at least an EXAMPLE rule here. */
static const Rule rules[] = {
	/* app_id             title       tags mask     isfloating   monitor */
	{ "Gimp_EXAMPLE",     NULL,       0,            1,           -1 }, /* Start on currently visible tags floating, not tiled */
	{ "firefox_EXAMPLE",  NULL,       1 << 8,       0,           -1 }, /* Start on ONLY tag "9" */
	{ "^kitty_EXAMPLE$",  NULL,       0,            0,           -1 },
};

/* layout(s) */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ NULL,       NULL }, /* terminate */
};

/* monitors */
/*
 * (x=-1, y=-1) causes a monitor to "autoconfigure" its position
 *
 * WARNING: Due to https://gitlab.freedesktop.org/xorg/xserver/-/issues/899
 * negative monitor positions other than (-1, -1) create problems for Xwayland
 * clients
 *
 * AT LEAST ONE monitor rule must exist. Define at least a NULL default rule here. */
static const MonitorRule monrules[] = {
    /* name       mfact  nmaster scale layout       rotate/reflect               x    y  resx resy rate mode adaptive*/
	{ "eDP-1",    0.5f,  1,      1,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,  1920, 0,  0,  0,  0.0f,  0,  0},
	{ "HDMI-A-1", 0.5f,  1,      1,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,  0,   0,   0,  0,  0.0f,  2,  0},
	/* { NULL,    0.55f, 1,      1,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL, -1,  -1,   0,  0,  0.0f,  0,  1}, */
};

/* keyboard */
static const struct xkb_rule_names xkb_rules = {
	/* can specify fields: rules, model, layout, variant, options */
	/* example:
	.options = "ctrl:nocaps",
	*/
	.options = NULL,
};

static const int repeat_rate = 30;
static const int repeat_delay = 200;

/* Trackpad */
static const int tap_to_click = 1;
static const int tap_and_drag = 1;
static const int drag_lock = 1;
static const int disable_while_typing = 1;
static const int left_handed = 0;
static const int middle_button_emulation = 0;

/* Natural scrolling */
static const int trackpad_natural_scrolling = 1;
static const int mouse_natural_scrolling = 0;

/* You can choose between:
LIBINPUT_CONFIG_SCROLL_NO_SCROLL
LIBINPUT_CONFIG_SCROLL_2FG
LIBINPUT_CONFIG_SCROLL_EDGE
LIBINPUT_CONFIG_SCROLL_ON_BUTTON_DOWN
*/
static const enum libinput_config_scroll_method scroll_method = LIBINPUT_CONFIG_SCROLL_2FG;

/* You can choose between:
LIBINPUT_CONFIG_CLICK_METHOD_NONE
LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS
LIBINPUT_CONFIG_CLICK_METHOD_CLICKFINGER
*/
static const enum libinput_config_click_method click_method = LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS;

/* You can choose between:
LIBINPUT_CONFIG_SEND_EVENTS_ENABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED_ON_EXTERNAL_MOUSE
*/
static const uint32_t send_events_mode = LIBINPUT_CONFIG_SEND_EVENTS_ENABLED;

/* You can choose between:
LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT
LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE
*/
static const enum libinput_config_accel_profile trackpad_accel_profile = LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT;
static const double trackpad_accel_speed = 0.0;
static const enum libinput_config_accel_profile mouse_accel_profile = LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT;
static const double mouse_accel_speed = 0.0;

/* You can choose between:
LIBINPUT_CONFIG_TAP_MAP_LRM -- 1/2/3 finger tap maps to left/right/middle
LIBINPUT_CONFIG_TAP_MAP_LMR -- 1/2/3 finger tap maps to left/middle/right
*/
static const enum libinput_config_tap_button_map button_map = LIBINPUT_CONFIG_TAP_MAP_LRM;

/* If you want to use the windows key for MODKEY, use WLR_MODIFIER_LOGO */
#define MODKEY WLR_MODIFIER_LOGO

#define TAGKEYS(KEY,SKEY,TAG) \
	{ MODKEY,                    KEY,            view,            {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL,  KEY,            toggleview,      {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_SHIFT, SKEY,           tag,             {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT,SKEY,toggletag, {.ui = 1 << TAG} }

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *browsercmd[] = { "chromium", NULL };
static const char *termcmd[] = { "footclient", NULL };
static const char *menucmd[] = { "mew-run", NULL };

static const Key keys[] = {
	/* Note that Shift changes certain key codes: c -> C, 2 -> at, etc. */
	/* modifier                  key                 function        argument */
	{ MODKEY,                    XKB_KEY_p,          spawn,          {.v = menucmd} },
    { MODKEY,                    XKB_KEY_space,      spawn,          {.v = menucmd} },
	{ MODKEY,                    XKB_KEY_Return,     spawn,          {.v = termcmd} },
    { MODKEY,                    XKB_KEY_b,          spawn,          {.v = browsercmd} },
    { MODKEY,                    XKB_KEY_z,          spawn,          SHCMD("zathura") },
    { MODKEY,                    XKB_KEY_a,          spawn,          SHCMD("thunar") },
    { MODKEY,                    XKB_KEY_s,          spawn,          SHCMD("footclient -T spotify spotify_player") },
    { MODKEY,                    XKB_KEY_e,          spawn,          SHCMD("footclient -T files sh -lc lf") },
    { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_M,          spawn,          SHCMD("footclient -T mpd ncmpcpp") },
	
    { MODKEY,                    XKB_KEY_r,          spawn,          SHCMD("power-menu -l") },
    { MODKEY,                    XKB_KEY_c,          spawn,          SHCMD("cliphist list | mew | cliphist decode | wl-copy") },
    { MODKEY,                    XKB_KEY_m,          spawn,          SHCMD("monitor-layout") },
    { MODKEY|WLR_MODIFIER_ALT,   XKB_KEY_m,          spawn,          SHCMD("wayland-graphics") },
    { MODKEY|WLR_MODIFIER_ALT,   XKB_KEY_l,          spawn,          SHCMD(". ~/.cache/wal/colors-plain && wlock -i $color2 -a $color3") },
    { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_R,          spawn,          SHCMD("power-menu -p") },
    { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_E,          spawn,          SHCMD("emoji-menu") },
    { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_C,          spawn,          SHCMD("colorpick") },

    { MODKEY,                    XKB_KEY_w,          spawn,          SHCMD("theme -s") },
    { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_W,          spawn,          SHCMD("theme -p") },
    { WLR_MODIFIER_ALT|WLR_MODIFIER_SHIFT,  XKB_KEY_W,  spawn,       SHCMD("theme -m") },
    { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_T,          spawn,          SHCMD("theme-menu") },

    { MODKEY,                    XKB_KEY_Left,       spawn,          SHCMD("volume -t") },
    { MODKEY,                    XKB_KEY_Right,      spawn,          SHCMD("volume -t") },
    { MODKEY,                    XKB_KEY_Up,         spawn,          SHCMD("volume -i 2") },
    { MODKEY,                    XKB_KEY_Down,       spawn,          SHCMD("volume -d 2") },

    { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Left,       spawn,          SHCMD("media -q -p") },
    { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Right,      spawn,          SHCMD("media -q -n") },
    { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Up,         spawn,          SHCMD("media -q -t") },
    { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Down,       spawn,          SHCMD("media -q -t") },
    { MODKEY|WLR_MODIFIER_CTRL,  XKB_KEY_Up,         spawn,          SHCMD("media -v -i 2") },
    { MODKEY|WLR_MODIFIER_CTRL,  XKB_KEY_Down,       spawn,          SHCMD("media -v -d 2") },
    { MODKEY|WLR_MODIFIER_CTRL,  XKB_KEY_m,          spawn,          SHCMD("media-menu") },

    { MODKEY|WLR_MODIFIER_ALT,   XKB_KEY_Left,       spawn,          SHCMD("brightness -s 0") },
    { MODKEY|WLR_MODIFIER_ALT,   XKB_KEY_Right,      spawn,          SHCMD("brightness -s 100") },
    { MODKEY|WLR_MODIFIER_ALT,   XKB_KEY_Up,         spawn,          SHCMD("brightness -i 10") },
    { MODKEY|WLR_MODIFIER_ALT,   XKB_KEY_Down,       spawn,          SHCMD("brightness -d 10") },

    { 0,             XKB_KEY_XF86AudioPrev,          spawn,          SHCMD("media -q -p") },
    { 0,             XKB_KEY_XF86AudioNext,          spawn,          SHCMD("media -q -n") },
    { 0,             XKB_KEY_XF86AudioPlay,          spawn,          SHCMD("media -q -t") },
    { 0,             XKB_KEY_XF86AudioPause,         spawn,          SHCMD("media -q -t") },

    { 0,             XKB_KEY_XF86MonBrightnessUp,    spawn,          SHCMD("brightness -i 10") },
    { 0,             XKB_KEY_XF86MonBrightnessDown,  spawn,          SHCMD("brightness -d 10") },

    { 0,             XKB_KEY_XF86AudioMute,          spawn,          SHCMD("volume -t") },
    { 0,             XKB_KEY_XF86AudioRaiseVolume,   spawn,          SHCMD("volume -i 2") },
    { 0,             XKB_KEY_XF86AudioLowerVolume,   spawn,          SHCMD("volume -d 2") },
    
    { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_S,          regions,        SHCMD("screenshot -a") },
    { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_D,          spawn,          SHCMD("screenshot -f") },
    { WLR_MODIFIER_ALT|WLR_MODIFIER_SHIFT, XKB_KEY_S, regions,       SHCMD("screenshot -as") },
    { WLR_MODIFIER_ALT|WLR_MODIFIER_SHIFT, XKB_KEY_D, spawn,         SHCMD("screenshot -fs") },
    
    { MODKEY|WLR_MODIFIER_CTRL,  XKB_KEY_b,          togglebar,      {0} },
	{ MODKEY,                    XKB_KEY_g,          togglegaps,     {0} },
    { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_P,          reload_colors,  {0} },
    { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_X,          addscratchpad,    {0} },
    { MODKEY|WLR_MODIFIER_CTRL,  XKB_KEY_x,          removescratchpad, {0} },
    { MODKEY,                    XKB_KEY_x,          togglescratchpad, {0} },
    { WLR_MODIFIER_ALT|WLR_MODIFIER_LOGO|WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT, XKB_KEY_Escape, togglepassthrough, {0} },
	
    { MODKEY,                    XKB_KEY_j,          focusstack,     {.i = +1} },
	{ MODKEY,                    XKB_KEY_k,          focusstack,     {.i = -1} },
	{ MODKEY,                    XKB_KEY_i,          incnmaster,     {.i = +1} },
	{ MODKEY,                    XKB_KEY_d,          incnmaster,     {.i = -1} },
	{ MODKEY,                    XKB_KEY_h,          setmfact,       {.f = -0.05f} },
	{ MODKEY,                    XKB_KEY_l,          setmfact,       {.f = +0.05f} },
    
    { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Return,     zoom,           {0} },
	{ MODKEY,                    XKB_KEY_Tab,        view,           {0} },
    { MODKEY,                    XKB_KEY_q,          killclient,     {0} },
    { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_space,      nextlayout,     {0} },
    { MODKEY,                    XKB_KEY_v,          togglefloating, {0} },
    { MODKEY,                    XKB_KEY_f,          togglefullscreen, {0} },
	
    { MODKEY|WLR_MODIFIER_CTRL,  XKB_KEY_j,          moveresizekb,   {.v = (int []){ 0, 40, 0, 0 }}},
    { MODKEY|WLR_MODIFIER_CTRL,  XKB_KEY_k,          moveresizekb,   {.v = (int []){ 0, -40, 0, 0 }}},
    { MODKEY|WLR_MODIFIER_CTRL,  XKB_KEY_l,          moveresizekb,   {.v = (int []){ 40, 0, 0, 0 }}},
    { MODKEY|WLR_MODIFIER_CTRL,  XKB_KEY_h,          moveresizekb,   {.v = (int []){ -40, 0, 0, 0 }}},

    { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_J,          moveresizekb,   {.v = (int []){ 0, 0, 0, 40 }}},
    { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_K,          moveresizekb,   {.v = (int []){ 0, 0, 0, -40 }}},
    { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_L,          moveresizekb,   {.v = (int []){ 0, 0, 40, 0 }}},
    { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_H,          moveresizekb,   {.v = (int []){ 0, 0, -40, 0 }}},
	
    { MODKEY,                    XKB_KEY_0,          view,           {.ui = ~0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_parenright, tag,            {.ui = ~0} },
	{ MODKEY,                    XKB_KEY_comma,      focusmon,       {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY,                    XKB_KEY_period,     focusmon,       {.i = WLR_DIRECTION_RIGHT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_less,       tagmon,         {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_greater,    tagmon,         {.i = WLR_DIRECTION_RIGHT} },
    { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Q,          quit,           {0} },

	TAGKEYS(          XKB_KEY_1, XKB_KEY_exclam,                     0),
	TAGKEYS(          XKB_KEY_2, XKB_KEY_at,                         1),
	TAGKEYS(          XKB_KEY_3, XKB_KEY_numbersign,                 2),
	TAGKEYS(          XKB_KEY_4, XKB_KEY_dollar,                     3),
	TAGKEYS(          XKB_KEY_5, XKB_KEY_percent,                    4),
	TAGKEYS(          XKB_KEY_6, XKB_KEY_asciicircum,                5),
	TAGKEYS(          XKB_KEY_7, XKB_KEY_ampersand,                  6),
	TAGKEYS(          XKB_KEY_8, XKB_KEY_asterisk,                   7),
	TAGKEYS(          XKB_KEY_9, XKB_KEY_parenleft,                  8),
/*
	{ MODKEY,                    XKB_KEY_t,          setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                    XKB_KEY_f,          setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                    XKB_KEY_m,          setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                    XKB_KEY_space,      setlayout,      {0} },
*/

	/* Ctrl-Alt-Backspace and Ctrl-Alt-Fx used to be handled by X server */
	{ WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_Terminate_Server, quit, {0} },
	/* Ctrl-Alt-Fx is used to switch to another VT, if you don't know what a VT is
	 * do not remove them.
	 */
#define CHVT(n) { WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_XF86Switch_VT_##n, chvt, {.ui = (n)} }
	CHVT(1), CHVT(2), CHVT(3), CHVT(4), CHVT(5), CHVT(6),
	CHVT(7), CHVT(8), CHVT(9), CHVT(10), CHVT(11), CHVT(12),
};

static const Button buttons[] = {
	{ ClkLtSymbol, 0,      BTN_LEFT,   setlayout,      {.v = &layouts[0]} },
	{ ClkLtSymbol, 0,      BTN_RIGHT,  setlayout,      {.v = &layouts[2]} },
	{ ClkTitle,    0,      BTN_MIDDLE, zoom,           {0} },
	{ ClkStatus,   0,      BTN_MIDDLE, spawn,          {.v = termcmd} },
	{ ClkClient,   MODKEY, BTN_LEFT,   moveresize,     {.ui = CurMove} },
	{ ClkClient,   MODKEY, BTN_MIDDLE, togglefloating, {0} },
	{ ClkClient,   MODKEY, BTN_RIGHT,  moveresize,     {.ui = CurResize} },
	{ ClkTagBar,   0,      BTN_LEFT,   view,           {0} },
	{ ClkTagBar,   0,      BTN_RIGHT,  toggleview,     {0} },
	{ ClkTagBar,   MODKEY, BTN_LEFT,   tag,            {0} },
	{ ClkTagBar,   MODKEY, BTN_RIGHT,  toggletag,      {0} },
};
