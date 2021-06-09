#include "VR-STL-Viewer.h"

#include "vtkCamera.h"
#include "vtkRenderer.h"
#include "vtkOpenGLRenderWindow.h"
#include "vtkActor.h"
#include "vtkOpenGLPolyDataMapper.h"
#include "vtkOpenGLVertexBufferObject.h"
#include "vtkSTLReader.h"
#include "vtkNew.h"
#include "vtkProperty.h"

#include "vtkRegressionTestImage.h"
#include "vtkTestUtilities.h"

#include "vtkRenderWindowInteractor.h"

#include "vtkOpenGLRenderWindow.h"

#include "vtkOpenVRCamera.h"
#include "vtkCullerCollection.h"
#include "vtkTransform.h"

#include "vtkPlaneWidget.h"

#include "vtkOpenVRRenderer.h"
#include "vtkOpenVRCamera.h"
#include "vtkOpenVRRenderWindow.h"
#include "vtkOpenVRRenderWindowInteractor.h"

#include "vtkWin32RenderWindowInteractor.h"
#include "vtkWin32OpenGLRenderWindow.h"
#include <string>

//----------------------------------------------------------------------------
int main(int argc, char* argv[])
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

	char* fileName = argv[1];
	vtkNew<vtkSTLReader> reader;
	reader->SetFileName(fileName);

	vtkNew<vtkOpenGLPolyDataMapper> mapper;
	mapper->SetInputConnection(reader->GetOutputPort());
	mapper->SetVBOShiftScaleMethod(vtkOpenGLVertexBufferObject::AUTO_SHIFT_SCALE);
	actor->SetMapper(mapper.Get());

	// the HMD may not be turned on/etc
	renderWindow->Initialize();
	if (renderWindow->GetHMD())
	{
		renderer->ResetCamera();
		renderWindow->Render();

		int retVal = vtkRegressionTestImage(renderWindow.Get());
		if (retVal == vtkRegressionTester::DO_INTERACTOR)
		{
			iren->Start();
		}
		return !retVal;
	}
	return EXIT_SUCCESS;
}
