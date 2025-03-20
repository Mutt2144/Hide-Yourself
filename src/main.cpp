#include <SDL2/SDL_opengl.h>
#include <iostream>

#include "engine/include/engine.h"
#include "engine/include/scene-model.h"
#include "engine/include/types.h"

ENGINE Engine;
Vector2 pos(0, 0);

GLuint texture;
GLuint mainText;
int textW, textH;

TEXT_UI text_ui;

class MenuScene : public SceneModel {
public:
    void handle_events(SDL_Event& e) {
    }

    void loop() {
        if (Engine.keys[K_DOWN]) pos.y += 1;

        Engine.Graphics.clear_window(Color4(0, 0, 0, 1));

        Engine.Graphics.draw_glTexture(texture, pos, Vector2(100, 100));

        Engine.Graphics.draw_glTexture(mainText, Vector2(50, 50), Vector2(textW, textH));

        //Engine.Graphics.draw_textUI(text_ui);

        Engine.Graphics.swap_buffers();
    }

    MenuScene(std::string name) : SceneModel(name, Engine) {}
};

MenuScene menuScene("Menu");

void loop() {
    while (Engine.running) {
        Engine.Timer.start();
        SDL_Event event = Engine.poll_events();
        if (event.type == SDL_QUIT) {
            Engine.running = false;
        }

        menuScene.loop();

        Engine.Timer.end();
    }
}

int main() {
    if (!Engine.init("Hide Yourself", Vector2(800, 600))) {
        Engine.quit();
        return 1;
    }

    Engine.Timer.set_fps(60);
    Engine.Graphics.load_image("assets/images/teste.png", GL_NEAREST, texture);
    Engine.Graphics.load_text_texture("Hello", "assets/fonts/BMSPA___.TTF", 24, Color4(1, 0.2f, 0.3f, 1.0f), mainText, textW, textH, 500, GL_LINEAR);

    text_ui.texture = mainText;
    text_ui.position = Vector2(50, 50);
    text_ui.size.x = textW;
    text_ui.size.y = textH;

    loop();

    Engine.Graphics.delete_image(texture);
    Engine.Graphics.delete_text_texture(mainText);
    Engine.quit();
    return 0;
}
