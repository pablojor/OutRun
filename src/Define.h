#pragma once

#define DISPLAY_BUFFER_NUM 2 // minimum 2 required
#define FLIP_RATE 0 // 0: no fliprate is set. 1: 30fps on 60Hz video output  2: 20fps
#define FLIP_MODE SCE_VIDEO_OUT_FLIP_MODE_VSYNC // SceVideoOutFlipMode

#define VIDEO_MEMORY_STACK_SIZE (1024 * 1024 * 192)

#define SLEEP_BEFORE_FINISH 2 // in seconds