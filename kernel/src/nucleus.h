struct __attribute__((aligned(4))) fb_info {
    unsigned int physicalWidth;   // #0 Physical Width
    unsigned int physicalHeight;  // #4 Physical Height
    unsigned int virtualWidth;    // #8 Virtual Width
    unsigned int virtualHeight;   // #12 Virtual Height
    unsigned int pitch;           // #16 GPU - Pitch
    unsigned int bitDepth;        // #20 Bit Depth
    unsigned int x;               // #24 X
    unsigned int y;               // #28 Y
    unsigned int gpuPointer;      // #32 GPU - Pointer
    unsigned int gpuSize;         // #36 GPU - Size
};

