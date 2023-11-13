#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <vector>
#include <algorithm>
struct Color {
    int red;
    int green;
    int blue;
    int alpha;
};

void printRGBAInfo(const Color &color) {
    // Ensure the values are within the range
    int red = std::min(std::max(color.red, 0), 255);
    int green = std::min(std::max(color.green, 0), 255);
    int blue = std::min(std::max(color.blue, 0), 255);
    int alpha = std::min(std::max(color.alpha, 0), 255);

    // Calculate hex value
    std::cout << "Red: " << red << std::endl;
    std::cout << "Green: " << green << std::endl;
    std::cout << "Blue: " << blue << std::endl;
    std::cout << "Alpha: " << alpha << std::endl;

    std::cout << "Hex: #" << std::hex << std::setw(2) << std::setfill('0') << red
              << std::setw(2) << std::setfill('0') << green
              << std::setw(2) << std::setfill('0') << blue
              << std::setw(2) << std::setfill('0') << alpha << std::dec << std::endl;

    // Convert RGB to HSL
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
}
bool parseColor(const std::string& colorStr, Color& color) {
    // Implement color parsing logic based on the given formats
    // Return true if parsing is successful, false otherwise
}

int main() {
       // Read color values from the 'colors.txt' file
  /* std::ifstream file("colors.txt");
    std::vector<Color> colors;

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            Color color;
            if (parseColor(line, color)) {
                colors.push_back(color);
            } else {
                std::cerr << "Warning: Ignoring invalid color in 'colors.txt': " << line << std::endl;
            }
        }
        file.close();
    } else {
        std::cerr << "Error: Unable to open 'colors.txt'." << std::endl;
        return 1;
    }
*/
std::cout << "Saturation: " << std::endl;
    //Color color = {245, 100, 100, 155}; // Example: Fully opaque red
    //printRGBAInfo(color);
    //return 1;

       std::ifstream file("colors.txt");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            Color color;
            if (iss >> color.red >> color.green >> color.blue >> color.alpha) {
                printRGBAInfo(color);
            } else {
                std::cout << "B³êdny format danych w pliku" << std::endl;
            }
        }
        file.close();
    } else {
        std::cout << "Nie uda³o siê otworzyæ pliku" << std::endl;
    }
    return 0;



}
