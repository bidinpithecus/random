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
bool menuVisible = false;

// Menu entry IDs
constexpr int MENU_ITEM_BUFFERS = 0;
constexpr int MENU_BOUNDING_VOLUMES = 1;
constexpr int MENU_SPATIAL_PARTITIONING = 2;
constexpr int MENU_EXIT = 27;

int menu;

// Menu entry labels
string itemBuffersLabel = "Item Buffers: ";
string boundingVolumesLabel = "Bounding Volumes: ";
string spatialPartitioningLabel = "Spatial Partitioning: ";

void renderUI();

void toggleOption(bool& option, string& label) {
    option = !option;
}

void mouse(int button, int state, int x, int y) {
	menuVisible = true;
	renderUI();

    cout << useItemBuffers << endl;
    cout << useBoundingVolumes << endl;
    cout << useSpatialPartitioning << endl << endl;
}

void handleMainMenu(int op) {
    switch (op) {
        case MENU_ITEM_BUFFERS:
            toggleOption(useItemBuffers, itemBuffersLabel);
            break;
        case MENU_BOUNDING_VOLUMES:
            toggleOption(useBoundingVolumes, boundingVolumesLabel);
            break;
        case MENU_SPATIAL_PARTITIONING:
            toggleOption(useSpatialPartitioning, spatialPartitioningLabel);
            break;
        case MENU_EXIT:
            cout << "See ya later" << endl;
            exit(0);
            break;
    }

	glutDestroyMenu(menu);

    glutPostRedisplay();
}

void renderUI() {
    string itemBuffersText = itemBuffersLabel + (useItemBuffers ? "ON" : "OFF");
    string boundingVolumesText = boundingVolumesLabel + (useBoundingVolumes ? "ON" : "OFF");
    string spatialPartitioningText = spatialPartitioningLabel + (useSpatialPartitioning ? "ON" : "OFF");

    menu = glutCreateMenu(handleMainMenu);
    glutAddMenuEntry(itemBuffersText.c_str(), MENU_ITEM_BUFFERS);
    glutAddMenuEntry(boundingVolumesText.c_str(), MENU_BOUNDING_VOLUMES);
    glutAddMenuEntry(spatialPartitioningText.c_str(), MENU_SPATIAL_PARTITIONING);
    glutAddMenuEntry("Exit", MENU_EXIT);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void idle(void) {
    getFps();
    glutPostRedisplay();
}

void drawScene() {
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
