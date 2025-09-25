#include"captureVideo.hpp"

captureVideo::captureVideo(int w, int h, int fps, const std::string& filename)
    : width(w), height(h), ffmpeg(nullptr) {

    // Commande ffmpeg
    std::string cmd = "ffmpeg -y -f rawvideo -pixel_format rgb24 -video_size "
        + std::to_string(width) + "x" + std::to_string(height) +
        " -framerate " + std::to_string(fps) +
        " -i - -pix_fmt yuv420p -vcodec libx264 " + filename;

    // Ouvrir un pipe vers ffmpeg
#ifdef _WIN32
    ffmpeg = _popen(cmd.c_str(), "wb");
#else
    ffmpeg = popen(cmd.c_str(), "w");
#endif
}

captureVideo::~captureVideo() {
    if (ffmpeg) {
#ifdef _WIN32
        _pclose(ffmpeg);
#else
        pclose(ffmpeg);
#endif
    }
}

void captureVideo::captureFrame() {
    if (!ffmpeg) return;

    std::vector<unsigned char> pixels(width * height * 3);
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());

    // OpenGL renvoie l’image inversée verticalement ? on flip ligne par ligne
    for (int y = height - 1; y >= 0; y--) {
        fwrite(&pixels[y * width * 3], 3, width, ffmpeg);
    }
}
