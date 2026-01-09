#pragma once
#include "sokol_gfx.h"

typedef struct {
    float uv_offset[2];
    float uv_scale[2];
} offscreen_vs_params_t;

static inline const sg_shader_desc* offscreen_shader_desc(sg_backend backend) {
    static sg_shader_desc desc = {0};
    static bool initialized = false;
    if (!initialized) {
        initialized = true;
        static const char vs_src[] = "#version 330\nlayout(location=0) in vec2 in_pos;\nlayout(location=1) in vec2 in_uv;\nout vec2 uv;\nvoid main() {\n  gl_Position = vec4(in_pos*2.0-1.0, 0.5, 1.0);\n  uv = in_uv;\n}\n";
        static const char fs_src[] = "#version 330\nuniform sampler2D tex;\nin vec2 uv;\nout vec4 frag_color;\nvoid main() {\n  frag_color = texture(tex, uv);\n}\n";
        desc.vertex_func.source = vs_src;
        desc.fragment_func.source = fs_src;
        desc.label = "offscreen_shader";
        desc.images[0].stage = SG_SHADERSTAGE_FRAGMENT;
        desc.images[0].image_type = SG_IMAGETYPE_2D;
        desc.samplers[0].stage = SG_SHADERSTAGE_FRAGMENT;
        desc.samplers[0].sampler_type = SG_SAMPLERTYPE_FILTERING;
        desc.image_sampler_pairs[0].image_slot = 0;
        desc.image_sampler_pairs[0].sampler_slot = 0;
        desc.image_sampler_pairs[0].stage = SG_SHADERSTAGE_FRAGMENT;
        desc.image_sampler_pairs[0].glsl_name = "tex";
    }
    return &desc;
}

static inline const sg_shader_desc* offscreen_pal_shader_desc(sg_backend backend) {
    static sg_shader_desc desc = {0};
    static bool initialized = false;
    if (!initialized) {
        initialized = true;
        static const char vs_src[] = "#version 330\nlayout(location=0) in vec2 in_pos;\nlayout(location=1) in vec2 in_uv;\nout vec2 uv;\nvoid main() {\n  gl_Position = vec4(in_pos*2.0-1.0, 0.5, 1.0);\n  uv = in_uv;\n}\n";
        static const char fs_src[] = "#version 330\nuniform sampler2D fb_tex;\nuniform sampler2D pal_tex;\nin vec2 uv;\nout vec4 frag_color;\nvoid main() {\n  float pix = texture(fb_tex, uv).x;\n  frag_color = vec4(texture(pal_tex, vec2(pix, 0.0)).xyz, 1.0);\n}\n";
        desc.vertex_func.source = vs_src;
        desc.fragment_func.source = fs_src;
        desc.label = "offscreen_pal_shader";
        desc.images[0].stage = SG_SHADERSTAGE_FRAGMENT;
        desc.images[0].image_type = SG_IMAGETYPE_2D;
        desc.images[1].stage = SG_SHADERSTAGE_FRAGMENT;
        desc.images[1].image_type = SG_IMAGETYPE_2D;
        desc.samplers[0].stage = SG_SHADERSTAGE_FRAGMENT;
        desc.samplers[0].sampler_type = SG_SAMPLERTYPE_FILTERING;
        desc.image_sampler_pairs[0].image_slot = 0;
        desc.image_sampler_pairs[0].sampler_slot = 0;
        desc.image_sampler_pairs[0].stage = SG_SHADERSTAGE_FRAGMENT;
        desc.image_sampler_pairs[0].glsl_name = "fb_tex";
        desc.image_sampler_pairs[1].image_slot = 1;
        desc.image_sampler_pairs[1].sampler_slot = 0;
        desc.image_sampler_pairs[1].stage = SG_SHADERSTAGE_FRAGMENT;
        desc.image_sampler_pairs[1].glsl_name = "pal_tex";
    }
    return &desc;
}

static inline const sg_shader_desc* display_shader_desc(sg_backend backend) {
    static sg_shader_desc desc = {0};
    static bool initialized = false;
    if (!initialized) {
        initialized = true;
        static const char vs_src[] = "#version 330\nlayout(location=0) in vec2 in_pos;\nlayout(location=1) in vec2 in_uv;\nout vec2 uv;\nvoid main() {\n  gl_Position = vec4(in_pos*2.0-1.0, 0.5, 1.0);\n  uv = in_uv;\n}\n";
        static const char fs_src[] = "#version 330\nuniform sampler2D tex;\nin vec2 uv;\nout vec4 frag_color;\nvoid main() {\n  frag_color = vec4(texture(tex, uv).xyz, 1.0);\n}\n";
        desc.vertex_func.source = vs_src;
        desc.fragment_func.source = fs_src;
        desc.label = "display_shader";
        desc.images[0].stage = SG_SHADERSTAGE_FRAGMENT;
        desc.images[0].image_type = SG_IMAGETYPE_2D;
        desc.samplers[0].stage = SG_SHADERSTAGE_FRAGMENT;
        desc.samplers[0].sampler_type = SG_SAMPLERTYPE_FILTERING;
        desc.image_sampler_pairs[0].image_slot = 0;
        desc.image_sampler_pairs[0].sampler_slot = 0;
        desc.image_sampler_pairs[0].stage = SG_SHADERSTAGE_FRAGMENT;
        desc.image_sampler_pairs[0].glsl_name = "tex";
    }
    return &desc;
}

#define UB_offscreen_vs_params (0)
#define IMG_fb_tex (0)
#define IMG_pal_tex (1)
#define IMG_tex (0)
#define SMP_smp (0)
