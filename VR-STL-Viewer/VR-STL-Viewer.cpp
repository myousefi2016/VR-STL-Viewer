#include "VR-STL-Viewer.h"

int vrRendering(const char* fileName)
{
	vtkNew<vtkOpenVRRenderer> renderer;
	vtkNew<vtkOpenVRRenderWindow> renderWindow;
	vtkNew<vtkOpenVRRenderWindowInteractor>  iren;
	vtkNew<vtkOpenVRCamera> cam;
	renderer->SetShowFloor(false);

	vtkNew<vtkActor> actor;
	renderer->SetBackground(0.0, 0.0, 0.0);
	renderWindow->AddRenderer(renderer.Get());
	renderer->AddActor(actor.Get());
	iren->SetRenderWindow(renderWindow.Get());
	renderer->SetActiveCamera(cam.Get());

	renderWindow->SetDesiredUpdateRate(350.0);
	iren->SetDesiredUpdateRate(350.0);
	iren->SetStillUpdateRate(350.0);

	renderer->RemoveCuller(renderer->GetCullers()->GetLastItem());

	vtkNew<vtkSTLReader> reader;
	reader->SetFileName(fileName);

	vtkNew<vtkPolyDataMapper> mapper;
	mapper->SetInputConnection(reader->GetOutputPort());
	actor->SetMapper(mapper.Get());

	renderWindow->Initialize();
	if (renderWindow->GetHMD())
	{
		renderer->ResetCamera();
		renderWindow->Render();

		renderWindow.Get();
		iren->Start();
	}
	return EXIT_SUCCESS;
}
