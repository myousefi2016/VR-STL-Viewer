#ifndef VRVIEWER_H
#define VRVIEWER_H

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

class Renderer
{
public:

	Renderer();
	~Renderer();

	const char* GetFilePath()
	{
		return filepath;
	}

	void SetFilePath(const char* fp)
	{
		filepath = fp;
	}

	void Render();
private:
	const char* filepath;
	vtkNew<vtkOpenVRRenderer> renderer;
	vtkNew<vtkOpenVRRenderWindow> renderWindow;
	vtkNew<vtkOpenVRRenderWindowInteractor>  iren;
	vtkNew<vtkOpenVRCamera> cam;
	vtkNew<vtkActor> actor;
	vtkNew<vtkSTLReader> reader;
	vtkNew<vtkPolyDataMapper> mapper;
};

#endif // VRVIEWER_H