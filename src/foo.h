
extern float a[256];
extern float b[256];
extern float c[256];

extern void foo(){
    for (int i=0; i<256; i++){
        a[i] = b[i] + c[i];
    }
}
