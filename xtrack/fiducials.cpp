// Fiducial tracking using libfidtrack (http://reactivision.sourceforge.net/)

#include "fiducials.h"

FiducialFinder::FiducialFinder(int width, int height) {
	initialize_treeidmap(&treeidmap);

	dmap = new ShortPoint[height * width];
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			dmap[y * width + x].x = x;
			dmap[y * width + x].y = y;
		}
	}

	initialize_fidtrackerX(&fidtrackerx, &treeidmap, dmap);
	initialize_segmenter(&segmenter, width, height, treeidmap.max_adjacencies);
}

FiducialFinder::~FiducialFinder() {
	delete dmap;
}

int FiducialFinder::findFiducials(cv::Mat *frame) {
	step_segmenter(&segmenter, frame->data);
	return find_fiducialsX(fiducials, MAX_FIDUCIALS,
			&fidtrackerx, &segmenter, frame->cols, frame->rows);
}
