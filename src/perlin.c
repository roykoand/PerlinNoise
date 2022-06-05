#include <Python.h>

// original code in Java https://mrl.cs.nyu.edu/~perlin/noise/

double fade(double t){
    return t * t * t * (t * (t * 6 - 15) + 10);
}

double lerp(double t, double a, double b) {
    return a + t * (b - a);
}

// https://stackoverflow.com/questions/10729891/perlin-noise-gradient-function
double grad2d(int hash, double x, double y) {
      return ((hash & 1) ? x : -x) + ((hash & 2) ? y : -y);
}

double grad3d(int hash, double x, double y, double z) {
      int h = hash & 15;
      double u = h<8 ? x : y,
             v = h<4 ? y : h==12||h==14 ? x : z;
      return ((h&1) == 0 ? u : -u) + ((h&2) == 0 ? v : -v);
}

double perlin2d(double x, double y){

    int X = (int) x & 255,
        Y = (int) y & 255;

    x -= (int) x;
    y -= (int) y;

    double u = fade(x),
           v = fade(y);

    int P[512] = { 151,160,137,91,90,15,
		131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,	
		190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
		88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
		77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
		102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
		135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
		5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
		223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
		129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
		251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
		49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
		138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
	};
    for (int i=0; i < 256; i++) {
        P[256+i] = P[i];
    }

    int A = P[X]+Y, AA = P[A], AB = P[A+1],   
        B = P[X+1]+Y, BA = P[B], BB = P[B+1];


    return lerp(v, lerp(u,           grad2d(P[AA  ], x  , y),
                                     grad2d(P[BA  ], x-1, y )),
                             lerp(u, grad2d(P[AB  ], x  , y-1),
                                     grad2d(P[BB  ], x-1, y-1)));
}

double perlin3d(double x, double y, double z){

    int X = (int) x & 255,
        Y = (int) y & 255,
        Z = (int) z & 255;

    x -= (int) x;
    y -= (int) y;
    z -= (int) z;

    double u = fade(x),
           v = fade(y),
           w = fade(z);

    int P[512] = { 151,160,137,91,90,15,
		131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,	
		190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
		88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
		77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
		102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
		135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
		5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
		223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
		129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
		251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
		49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
		138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
	};
    for (int i=0; i < 256; i++) {
        P[256+i] = P[i];
    }

    int A = P[X]+Y, AA = P[A]+Z, AB = P[A+1]+Z,   
        B = P[X+1]+Y, BA = P[B]+Z, BB = P[B+1]+Z;


    return lerp(w, lerp(v, lerp(u,   grad3d(P[AA  ], x  , y  , z   ),
                                     grad3d(P[BA  ], x-1, y  , z   )),
                             lerp(u, grad3d(P[AB  ], x  , y-1, z   ),
                                     grad3d(P[BB  ], x-1, y-1, z   ))),
                     lerp(v, lerp(u, grad3d(P[AA+1], x  , y  , z-1 ),
                                     grad3d(P[BA+1], x-1, y  , z-1 )),
                             lerp(u, grad3d(P[AB+1], x  , y-1, z-1 ),
                                     grad3d(P[BB+1], x-1, y-1, z-1 ))));
}


static PyObject *perlin2d_noise(PyObject *self, PyObject *args) {

    double x, y;

    if(!PyArg_ParseTuple(args, "dd", &x, &y)) {
        return NULL;

    }

    return PyFloat_FromDouble(perlin2d(x, y));

}

static PyObject *perlin3d_noise(PyObject *self, PyObject *args) {

    double x, y, z;

    if(!PyArg_ParseTuple(args, "ddd", &x, &y, &z)) {
        return NULL;

    }
    
    return PyFloat_FromDouble(perlin3d(x, y, z));

}


static PyMethodDef perlin_noises[] = {
    {"perlin2d", perlin2d_noise, METH_VARARGS, "Perlin 3d noise"},
    {"perlin3d", perlin3d_noise, METH_VARARGS, "Perlin 2d noise"},
    {NULL, NULL, 0, NULL}
};


static struct PyModuleDef perlinnoisemodule = {
    PyModuleDef_HEAD_INIT,
    "perlin",
    "Module to generate perlin noise",
    -1,
    perlin_noises
};

PyMODINIT_FUNC PyInit_perlin(void) {
    return PyModule_Create(&perlinnoisemodule);
}