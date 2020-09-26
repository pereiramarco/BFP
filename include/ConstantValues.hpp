#pragma once

class ConstantValues {
    public:
        static const int screenSizeH=1080;
        static const int screenSizeW=1920;
        static const int localMapSizeW=50;
        static const int localMapSizeH=50;
        static const int localTileW=64;
        static const int localTileH=64;
        static const int mapW=80;
        static const int mapH=45;
        static const int worldTileW=24;
        static const int worldTileH=24;
        static constexpr float playerLocalPosX=screenSizeW/(2*localTileW);
        static constexpr float playerLocalPosY=screenSizeH/(2*localTileH);
        static const int UIFRAMEx = 15;
        static const int UIFRAMEy = 15;
};