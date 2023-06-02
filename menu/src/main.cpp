#include "App.hpp"
#include "Shapes.hpp"
#include "Coordinate.hpp"
#include "Helpers.hpp"

using namespace std;

int height = WINDOW_HEIGHT;
int width = WINDOW_WIDTH;
int xPos = 0;
int yPos = 0;
bool isFullScreen = false;
int frameCount = 0;
int currentTime = 0;
int previousTime = 0;
float fps = 0.0;

bool useItemBuffers = false;
bool useBoundingVolumes = false;
bool useSpatialPartitioning = false;

// Menu entry labels
string itemBuffersLabel = "Item Buffers: ";
string boundingVolumesLabel = "Bounding Volumes: ";
string spatialPartitioningLabel = "Spatial Partitioning: ";

void renderUI();

void toggleOption(bool& option, string& label) {
    option = !option;
    label = label.substr(0, label.find(':') + 2) + (option ? "ON" : "OFF");
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        renderUI();
    }

    cout << useItemBuffers << endl;
    cout << useBoundingVolumes << endl;
    cout << useSpatialPartitioning << endl << endl;
}

void handleMainMenu(int op) {
    switch (op) {
        case 0:
            toggleOption(useItemBuffers, itemBuffersLabel);
            break;
        case 1:
            toggleOption(useBoundingVolumes, boundingVolumesLabel);
            break;
        case 2:
            toggleOption(useSpatialPartitioning, spatialPartitioningLabel);
            break;
        case 27:
            cout << "See ya later" << endl;
            exit(0);
            break;
    }

    glutPostRedisplay();
}

void renderUI() {
    int menu;

    string itemBuffersText = itemBuffersLabel + (useItemBuffers ? "ON" : "OFF");
    string boundingVolumesText = boundingVolumesLabel + (useBoundingVolumes ? "ON" : "OFF");
    string spatialPartitioningText = spatialPartitioningLabel + (useSpatialPartitioning ? "ON" : "OFF");

    menu = glutCreateMenu(handleMainMenu);
    glutAddMenuEntry(itemBuffersText.c_str(), 0);
    glutAddMenuEntry(boundingVolumesText.c_str(), 1);
    glutAddMenuEntry(spatialPartitioningText.c_str(), 2);
    glutAddMenuEntry("Exit", 27);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void idle(void) {
    getFps();
    glutPostRedisplay();
}

void drawScene() {
    // Your scene rendering code goes here
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Menu");
    glutReshapeFunc(resize);
    glutKeyboardFunc(normalKeyPressed);
    glutSpecialFunc(specialKeyPressed);
    glutMouseFunc(mouse);
    glutDisplayFunc(renderScene);
    glutIdleFunc(idle);
    setupRC();
    renderUI(); // Render the initial UI

    glutMainLoop();

    return 0;
}
