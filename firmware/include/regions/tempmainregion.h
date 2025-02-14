#ifndef TEMPREGION_H
#define TEMPREGION_H

#include "display_region.h"
#include "config.h"

namespace ModFirmWare
{
  class LogEngine;
}

namespace KitchenClock
{
  class TempProbe;

  class TempMainRegion : public ModFirmWare::DisplayRegion
  {
  public:
    TempMainRegion(ModFirmWare::TFTDisplay *display,  ModFirmWare::DisplayRegion::window_t window);

    void updateCanvas() override;

    void setProbe(uint ix, TempProbe* probe);
    void triggerUpdate() { newvalues = true; }

    void enableCalibrationMode(const bool calibration); 
    inline const int getSelectedProbeIx() const { return selectedProbeIx; } 

    int selectNextProbe();
    int selectPrevProbe();
    void unselectProbes();

  protected:
    bool isUpdated() const;

  private:
    TempProbe* probes[NUM_PROBES];
    bool newvalues;
    bool calibration;
    int selectedProbeIx;

    void printTempBlock(uint ix);
    void printCalibrationBlock(uint ix);
    const int checkIfProbeCanBeSelected(const int pix);
  };
}

#endif // TEMPREGION_H