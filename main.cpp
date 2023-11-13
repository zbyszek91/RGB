#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>

struct Color {
    int red;
    int green;
    int blue;
    int alpha;
};

void printColorInfo(const Color &color) {
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
    double lightness = (cmax + cmin) / 2;
    std::cout << "Hue: " << round(hue) << std::endl;
    std::cout << "Saturation: " << std::fixed << std::setprecision(2) << saturation << std::endl;
    std::cout << "Lightness: " << std::fixed << std::setprecision(2) << lightness << std::endl;


}

Color mixColors(const std::vector<Color> &colors) {
    int totalRed = 0, totalGreen = 0, totalBlue = 0, totalAlpha = 0;
    for (const auto &color : colors) {
        totalRed += color.red;
        totalGreen += color.green;
        totalBlue += color.blue;
        totalAlpha += color.alpha;
    }
    int avgRed = totalRed / colors.size();
    int avgGreen = totalGreen / colors.size();
    int avgBlue = totalBlue / colors.size();
    int avgAlpha = totalAlpha / colors.size();

    Color result = {avgRed, avgGreen, avgBlue, avgAlpha};
    return result;
}

Color lowestColor(const std::vector<Color> &colors) {
    auto lowestRed = std::min_element(colors.begin(), colors.end(), [](const Color &a, const Color &b) {
        return a.red < b.red;
    })->red;

    auto lowestGreen = std::min_element(colors.begin(), colors.end(), [](const Color &a, const Color &b) {
        return a.green < b.green;
    })->green;

    auto lowestBlue = std::min_element(colors.begin(), colors.end(), [](const Color &a, const Color &b) {
        return a.blue < b.blue;
    })->blue;

    auto lowestAlpha = std::min_element(colors.begin(), colors.end(), [](const Color &a, const Color &b) {
        return a.alpha < b.alpha;
    })->alpha;

    return {lowestRed, lowestGreen, lowestBlue, lowestAlpha};
}

Color highestColor(const std::vector<Color> &colors) {
    auto highestRed = std::max_element(colors.begin(), colors.end(), [](const Color &a, const Color &b) {
        return a.red < b.red;
    })->red;

    auto highestGreen = std::max_element(colors.begin(), colors.end(), [](const Color &a, const Color &b) {
        return a.green < b.green;
    })->green;

    auto highestBlue = std::max_element(colors.begin(), colors.end(), [](const Color &a, const Color &b) {
        return a.blue < b.blue;
    })->blue;

    auto highestAlpha = std::max_element(colors.begin(), colors.end(), [](const Color &a, const Color &b) {
        return a.alpha < b.alpha;
    })->alpha;

    return {highestRed, highestGreen, highestBlue, highestAlpha};
}

Color mixSaturate(const std::vector<Color> &colors) {
    double avgSaturation = 0.0;
    for (const auto &color : colors) {
        double r = static_cast<double>(color.red) / 255;
        double g = static_cast<double>(color.green) / 255;
        double b = static_cast<double>(color.blue) / 255;

        double cmax = std::fmax(r, std::fmax(g, b));
        double cmin = std::fmin(r, std::fmin(g, b));
        double delta = cmax - cmin;

        double saturation = (cmax == 0) ? 0 : delta / cmax;
        avgSaturation += saturation;
    }

    avgSaturation /= colors.size();

    int saturation = static_cast<int>(avgSaturation * 255);

    return {saturation, saturation, saturation, saturation};
}

int main() {
    std::ifstream file("colors.txt");
    if (file.is_open()) {
        std::string line;
        std::vector<Color> colors;

        while (std::getline(file, line)) {
            std::istringstream iss(line);
            Color color;
            if (iss >> color.red >> color.green >> color.blue >> color.alpha) {
                colors.push_back(color);
            } else {
                std::cout << "Invalid data format in the file" << std::endl;
            }
        }
        file.close();

        std::cout << " select mod: mix lowest higest mix-Saturate" << std::endl;
        std::string mode = "mix";
        std::cin>>mode;
        //std::string mode = "mix";
        if (!colors.empty()) {
            Color resultColor;
            if (mode == "lowest") {
                resultColor = lowestColor(colors);
            } else if (mode == "highest") {
                resultColor = highestColor(colors);
            } else if (mode == "mix-saturate") {
                resultColor = mixSaturate(colors);
            } else {
                resultColor = mixColors(colors);
            }

            printColorInfo(resultColor);

        } else {
            std::cout << "No data found in the file" << std::endl;
        }
    } else {
        std::cout << "Unable to open the file" << std::endl;
    }
    return 0;
}

