#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cmath>

struct RGBAColor {
    int red;
    int green;
    int blue;
    int alpha;
};

// Function to print RGBA information
void printRGBAInfo(const RGBAColor &color) {
    int red = std::min(std::max(color.red, 0), 255);
    int green = std::min(std::max(color.green, 0), 255);
    int blue = std::min(std::max(color.blue, 0), 255);
    int alpha = std::min(std::max(color.alpha, 0), 255);

    std::cout << "Red: " << red << std::endl;
    std::cout << "Green: " << green << std::endl;
    std::cout << "Blue: " << blue << std::endl;
    std::cout << "Alpha: " << alpha << std::endl;

    std::cout << "Hex: #" << std::hex << std::setw(2) << std::setfill('0') << red
              << std::setw(2) << std::setfill('0') << green
              << std::setw(2) << std::setfill('0') << blue
              << std::setw(2) << std::setfill('0') << alpha << std::dec << std::endl;

    double r = static_cast<double>(red) / 255;
    double g = static_cast<double>(green) / 255;
    double b = static_cast<double>(blue) / 255;

    double cmax = std::fmax(r, std::fmax(g, b));
    double cmin = std::fmin(r, std::fmin(g, b));
    double delta = cmax - cmin;

    double hue = 0;
    if (delta != 0) {
        if (cmax == r) {
            hue = 60 * fmod(((g - b) / delta), 6);
        } else if (cmax == g) {
            hue = 60 * (((b - r) / delta) + 2);
        } else {
            hue = 60 * (((r - g) / delta) + 4);
        }
    }

    double saturation = (cmax == 0) ? 0 : delta / cmax;

    std::cout << "Hue: " << round(hue) << std::endl;
    std::cout << "Saturation: " << std::fixed << std::setprecision(2) << saturation << std::endl;
    std::cout << "-------------------" << std::endl;
}

int main() {
    std::ifstream file("colors.txt");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            RGBAColor color;
            if (iss >> color.red >> color.green >> color.blue >> color.alpha) {
                printRGBAInfo(color);
            } else {
                std::cout << "Invalid data format in the file" << std::endl;
            }
        }
        file.close();
    } else {
        std::cout << "Unable to open the file" << std::endl;
    }
    return 0;
}
