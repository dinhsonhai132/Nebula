#include "game.hpp"

Engine engine;

SUNY_API struct Sobj* Sdraw_rect_builtin(struct Sframe* frame) {

    struct Sobj* b = Sframe_pop(frame);
    struct Sobj* g = Sframe_pop(frame);
    struct Sobj* r = Sframe_pop(frame);
    struct Sobj* h = Sframe_pop(frame);
    struct Sobj* w = Sframe_pop(frame);
    struct Sobj* y = Sframe_pop(frame);
    struct Sobj* x = Sframe_pop(frame);

    engine.draw_rect(
        ValueOf(x),
        ValueOf(y),
        ValueOf(w),
        ValueOf(h),
        ValueOf(r),
        ValueOf(g),
        ValueOf(b)
    );

    MOVETOGC(x, frame->gc_pool);
    MOVETOGC(y, frame->gc_pool);
    MOVETOGC(w, frame->gc_pool);
    MOVETOGC(h, frame->gc_pool);
    MOVETOGC(r, frame->gc_pool);
    MOVETOGC(g, frame->gc_pool);
    MOVETOGC(b, frame->gc_pool);

    return null_obj;
}

void GameRun(char* file) {

    struct Suny* suny = SunyNew();

    suny->file = file;

    Ssymbol_add(suny->table, "init", 80);
    Ssymbol_add(suny->table, "draw", 81);
    Ssymbol_add(suny->table, "update", 82);

    Ssymbol_add(suny->table, "width", 83);
    Ssymbol_add(suny->table, "height", 84);
    Ssymbol_add(suny->table, "title", 85);

    SunyInstallLibrary(suny->frame, suny->compiler, suny->table);

    Sinitialize_c_api_func(suny->frame, suny->table, 86, 7, "draw_rect", (void*) Sdraw_rect_builtin);

    SunyRunFile(suny);

    struct Sobj* f_init = Sframe_load_global(suny->frame, 80);
    Svm_call_function(suny->frame, f_init->f_value);

    struct Sobj* v_width = Sframe_load_global(suny->frame, 83)->f_value;
    struct Sobj* v_height = Sframe_load_global(suny->frame, 84)->f_value;
    struct Sobj* v_title = Sframe_load_global(suny->frame, 85)->f_value;

    struct Sobj* f_update = Sframe_load_global(suny->frame, 82);
    struct Sobj* f_draw = Sframe_load_global(suny->frame, 81);

    if (v_title->type != STRING_OBJ) {
        printf("Error title must be a string\n");
        return;
    }

    if (!engine.init(ValueOf(v_width), ValueOf(v_height), tget_str(v_title)->string)) {
        printf("Engine init failed!\n");
        return;
    }

    Uint32 last = SDL_GetTicks();

    while (engine.is_running())
    {
        engine.poll_events();

        Uint32 now = SDL_GetTicks();
        float dt = (now - last) / 1000.0f;
        last = now;

        engine.clear(0.1f, 0.1f, 0.1f);

        Sframe_push_number(suny->frame, dt);
        Svm_call_function(suny->frame, f_update->f_value);

        Svm_call_function(suny->frame, f_draw->f_value);

        engine.present();
    }

    engine.shutdown();
}