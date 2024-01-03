#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

// Length of the gradient
#define GRADIENT_SIZE 1024

using namespace sf;

int main() {
	int iterations = 40;
	Vector2f center = { -0.2f, 0.0f };
	float zoom = 1.0;
	float velocity = 0.01f;
	float zoomFactor = 0.04f;

	Vector3f colors[GRADIENT_SIZE];
	Image gradient;
	gradient.loadFromFile("../assets/gradients/blue-to-yellow.png");

	for (size_t i = 0; i < GRADIENT_SIZE; i++) {
		auto p = gradient.getPixel(i, 0);
		colors[i] = Vector3f(p.r, p.g, p.b) / 256.0f;
	}

	RenderWindow window(VideoMode(1200, 900), "Mandelbrot Set");
	RectangleShape screen(Vector2f(window.getSize()));

	Font font;
	font.loadFromFile("../assets/fonts/Secular-One.ttf");

	Text textInfo;
	textInfo.setFont(font);
	textInfo.setCharacterSize(30);

	textInfo.setPosition(10, 10);
	textInfo.setOutlineColor(Color::Black);
	textInfo.setOutlineThickness(1);

	Shader shader;
	if (!shader.loadFromFile("mandelbrot.frag", Shader::Fragment)) {
		return EXIT_FAILURE;
	}

	shader.setUniform("resolution", Vector2f(window.getSize()));
	shader.setUniform("center", center);
	shader.setUniform("max_iteration", iterations);
	shader.setUniform("zoom", zoom);
	shader.setUniformArray("colors", colors, GRADIENT_SIZE);

	auto zoomIn = [&]() {
		zoom /= (1 + zoomFactor);

		if (zoom < 1E-5) zoom = 1E-5;
		else iterations++;
	};

	auto zoomOut = [&]() {
		zoom /= (1 - zoomFactor);

		if (zoom > 1.0f) zoom = 1.0f;
		else iterations--;
	};

	auto roundTo = [](double value) {
		return std::round(value * 1e6) / 1e6;
	};

	while (window.isOpen()) {
		Event event;

		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}

			if (event.type == Event::Resized) {
				FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(View(visibleArea));
				screen.setSize(Vector2f(event.size.width, event.size.height));
			}

			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Equal)
					zoomIn();
				else if (event.key.code == Keyboard::Dash)
					zoomOut();
			}

			if (event.type == Event::MouseWheelMoved) {
				if (event.mouseWheel.delta > 0)
					zoomIn();
				else if (event.mouseWheel.delta < 0)
					zoomOut();
			}

			if (Keyboard::isKeyPressed(Keyboard::LAlt)) {
				iterations--;
			}

			if (Keyboard::isKeyPressed(Keyboard::RAlt)) {
				iterations++;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::LShift)) {
			velocity = 0.001f;
		} else {
			velocity = 0.01f;
		}

		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			center.y += velocity * zoom;
			if (center.y > 1.0f)
				center.y = 1.0f;
		}

		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			center.y -= velocity * zoom;
			if (center.y < -1.0f)
				center.y = -1.0f;
		}

		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			center.x -= velocity * zoom;
			if (center.x < -1.0f)
				center.x = -1.0f;
		}

		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			center.x += velocity * zoom;
			if (center.x > 1.0f)
				center.x = 1.0f;
		}

		shader.setUniform("resolution", Vector2f(window.getSize()));
		shader.setUniform("max_iteration", iterations);
		shader.setUniform("center", center);
		shader.setUniform("zoom", zoom);

		window.clear(Color::Black);
		window.draw(screen, &shader);

		std::stringstream ss;

		ss << "Position: (" << roundTo(2.5 * center.x * float(window.getSize().x) / window.getSize().y) << ";\t" << roundTo(center.y * 2.5) << ")" << std::endl
		   << "Zoom: " << 1.0 / zoom << "x" << std::endl
		   << "Iterations: " << iterations << std::endl;

		textInfo.setString(ss.str());

		window.draw(textInfo);

		VertexArray cross(Lines);
		auto center = Vector2f(window.getSize()) / 2.0f;
		cross.append(Vertex(Vector2f(center.x - 10, center.y), Color::White));
		cross.append(Vertex(Vector2f(center.x + 10, center.y), Color::White));
		cross.append(Vertex(Vector2f(center.x, center.y - 10), Color::White));
		cross.append(Vertex(Vector2f(center.x, center.y + 10), Color::White));
		window.draw(cross);

		window.display();
	}

	return EXIT_SUCCESS;
}
