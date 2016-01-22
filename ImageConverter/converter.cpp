#include <iostream>
#include <fstream>

int main() {
    std::ifstream image("oldImage.bmp", std::ios::binary | std::ios::ate);
	std::streamsize sizeImage = image.tellg();
	sizeImage -= 62; // from the beginning
	sizeImage -= 2; // from the end
	image.seekg(62, std::ios::beg);
    auto buffer = new char[sizeImage];
	if (image.read(buffer, sizeImage)) {
		std::cout << "Read image!\n";
	}

    // moving bytes in right order
	for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 16; j++)
            std::swap(buffer[i * 16 + j], buffer[(127 - i) * 16 + j]);
	}
    // inverting bits for right colors
	for (int i = 0; i < sizeImage; i++)
        buffer[i] = (buffer[i] ^ ((1 << 8) - 1));

	std::ofstream newImage("image.bmp", std::ofstream::binary);
	if (newImage.write(buffer, sizeImage)) {
		std::cout << "Wrote image!\n";
	}

    return 0;
}
