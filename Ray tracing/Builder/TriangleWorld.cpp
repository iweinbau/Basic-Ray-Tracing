//
//  TriangleWorld.cpp
//  raytracer
//
//  Created by Iwein Bau on 17/03/2019.
//  Copyright © 2019 Iwein Bau. All rights reserved.
//

#include <stdio.h>

#include "./TriangleWorld.hpp"

#include "../3D-Model-Parser/OBJ-Loader/Loader/MeshLoader.hpp"
#include "../3D-Model-Parser/OBJ-Loader/Mesh/Mesh.hpp"

#include "../Objects/Plane.hpp"

#include "../Objects/Triangle.hpp"
#include "../Objects/SmoothTriangle.hpp"
#include "../Objects/Grid.hpp"
#include "../Material/Phong.hpp"
#include "../Material/Reflective.hpp"
#include "../Material/Mirror.hpp"
#include "../Objects/Instance.hpp"
#include "../Objects/Rectangle.hpp"
#include "../Light/AreaLight.hpp"


void TriangleWorld::buildWorld(){
    //PointLight light(Vect3(1, 1,1), Vect3(5,5, -5),500);

    Phong * reflective = new Phong(
                                       Lambertian(0.25,Vect3(0.3)),
                                       Lambertian(0.6,Vect3(0.4)),
                                   Specular(0.9,5,Vect3(0.6)));//,
                                     //Glossy(1,10,Vect3(1,1,1)));
    
    Rectangle* r = new Rectangle(Vect3(-5,5,-5),Vect3(10,0,0),Vect3(0,0,10));
    AreaLight* light = new AreaLight(r,Vect3(1),200);
    add_Light(light);
    
    

    MeshLoader::OBJLoader objLoader;
    objLoader.loadMesh("./Objects/cube.obj");
    Mesh mesh = objLoader.getLoadedMesh();
    
    Grid* grid = new Grid(mesh,reflective);
    
    Instance* instance = new Instance(grid,reflective);
    instance->scale(Vect3(2,2,2));
    instance->rotateY(45);
    instance->rotateX(45);
    instance->translate(Vect3(0,0,2));

    
    Phong* planem = new Phong(
                              Lambertian(0.25,Vect3(0.8,0.8,0.8)),
                              Lambertian(0.6,Vect3(0.8,0.8,0.8)),
                              Specular(0.2,5,Vect3(1,1,1)));
    Phong* planeb = new Phong(
                              Lambertian(0.25,Vect3(0.8,0.8,0.8)),
                              Lambertian(0.6,Vect3(0.8,0.8,0.8)),
                              Specular(0.2,1,Vect3(1,1,1)));
    
    Phong* planel = new Phong(
                              Lambertian(0.25,Vect3(0.8,0,0)),
                              Lambertian(0.6,Vect3(0.8,0,0)),
                              Specular(0.2,5,Vect3(1,1,1)));
    Phong* planer = new Phong(
                              Lambertian(0.25,Vect3(0,0.8,0)),
                              Lambertian(0.5,Vect3(0,0.8,0)),
                              Specular(0.2,5,Vect3(1,1,1)));
    
    Plane* planeback = new Plane(Point3(0, 0, -5), Normal(0,0,1),planem);
    Plane* planeleft = new Plane(Point3(-5, 0, 0), Normal(1,0,0),planel);
    Plane* planeright = new Plane(Point3(5, 0, 0), Normal(-1,0,0),planer);
    Plane* planebottom = new Plane(Point3(0, -5, 0), Normal(0,1,0),planeb);
    //Plane* planetop =  new Plane(Point3(0, 5, 0), Normal(0,-1,0),planem);
    
    add_object(planeback);
    add_object(planeleft);
    add_object(planeright);
    add_object(planebottom);
    //add_object(planetop);
    add_object(instance);

}
