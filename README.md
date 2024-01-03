# Mandelbrot Set Visualization

This repository contains a Mandelbrot set visualization program implemented in C++ using [Simple and Fast Multimedia Library (SFML)](https://github.com/SFML/SFML) for graphics rendering. Additionally, the visualization benefits from GLSL fragment shaders for efficient computation of the Mandelbrot set.

## Features

- Real-time rendering of the Mandelbrot set with smooth zoom and pan functionalities.
- Utilizes GLSL fragment shaders for accelerated computation.
- Interactive user interface for navigation and exploration.
- Customizable parameters for the Mandelbrot set rendering.

## Usage

- Use arrow keys to pan the view.
- Scroll up/down to zoom in/out (or use `+/-` keys).
- Adjust parameters for different visualizations.
- Increase/decrease the number of iterations with `Right/Left Alt` key.
- To move around the screen more slowly, hold down `Shift`

## Customization

Load different gradient from `assets/gradients` folder (or add your custom gradient - image with ratio 1024x10).
- Rainbow:
  ![rainbow.png](assets/gradients/rainbow.png)
- Pastel:
  ![pastel.png](assets/gradients/pastel.png)
- Green-Red-Blue:
  ![green-red-blue.png](assets/gradients/green-red-blue.png)
- Blue to yellow:
  ![blue-to-yellow.png](assets/gradients/blue-to-yellow.png)
- Aquarelle:
  ![aquarelle.png](assets/gradients/aquarelle.png)

Also you can customize some parameters:
- `iterations`: Maximum iterations for Mandelbrot set computation.
- `zoomFactor`: Zoom sensitivity.
- `velocity`: The velocity at which you move around the screen

## Examples

![image1.png](assets/images/image1.png)

![image2.png](assets/images/image2.png)

![image3.png](assets/images/image3.png)

![image4.png](assets/images/image4.png)

![image5.png](assets/images/image5.png)

![image6.png](assets/images/image6.png)

## License

This Mandelbrot set visualization program is open-source and available under the [MIT License](LICENSE). Feel free to use, modify, and distribute it.

## Acknowledgments

Special thanks to the SFML and GLSL communities for providing excellent tools and resources for graphics programming.

Happy fractal exploring! 🌀
