// VR-STL-Viewer.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include "vtkActor.h"
#include "vtkPolyDataMapper.h"
#include "vtkSTLReader.h"
#include "vtkNew.h"

#include "vtkCullerCollection.h"

#include "vtkOpenVRRenderer.h"
#include "vtkOpenVRCamera.h"
#include "vtkOpenVRRenderWindow.h"
#include "vtkOpenVRRenderWindowInteractor.h"

extern int vrRendering(const char* fileName);

// TODO: Reference additional headers your program requires here.
