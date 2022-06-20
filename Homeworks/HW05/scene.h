#ifndef SCENE_H
#define SCENE_H

#include "mathematics.h"

/* You can edit the scene by inserting or deleting spheres here */
const sphere spheres[] = {
    { /*radius*/1e5,  /*position*/{1e5+1,40.8,81.6},   /*emission*/{0,0,0},    /*color*/{.75,.25,.25},    /*material*/DIFFUSE    }, /* Left */
    { /*radius*/1e5,  /*position*/{-1e5+99,40.8,81.6}, /*emission*/{0,0,0},    /*color*/{.25,.25,.75},    /*material*/DIFFUSE    }, /* Right */
    { /*radius*/1e5,  /*position*/{50,40.8,1e5},       /*emission*/{0,0,0},    /*color*/{.75,.75,.75},    /*material*/DIFFUSE    }, /* Back */
    { /*radius*/1e5,  /*position*/{50,40.8,-1e5+170},  /*emission*/{0,0,0},    /*color*/{0,0,0},          /*material*/DIFFUSE    }, /* Front */
    { /*radius*/1e5,  /*position*/{50,1e5,81.6},       /*emission*/{0,0,0},    /*color*/{.75,.75,.75},    /*material*/DIFFUSE    }, /* Bottom */
    { /*radius*/1e5,  /*position*/{50,-1e5+81.6,81.6}, /*emission*/{0,0,0},    /*color*/{.75,.75,.75},    /*material*/DIFFUSE    }, /* Top */
    { /*radius*/16.5, /*position*/{27,16.5,47},        /*emission*/{0,0,0},    /*color*/{.999,.999,.999}, /*material*/SPECULAR   }, /* Mirror ball */
    { /*radius*/16.5, /*position*/{73,16.5,78},        /*emission*/{0,0,0},    /*color*/{.999,.999,.999}, /*material*/REFRACTIVE }, /* Glass ball */
    { /*radius*/600,  /*position*/{50,681.6-.27,81.6}, /*emission*/{12,12,12}, /*color*/{0,0,0},          /*material*/DIFFUSE    }, /* Top light */
};

/* You may also have to edit this variable if you want to edit the scene */
const float camera_offset = 140.0f;

#endif