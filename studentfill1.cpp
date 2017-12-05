
#include "studentfill1.h"
#include <QDebug>


void recursiveFill(int r, int k, IDrawingParent *im, QColor colorOld, QColor colorNew)
{
    if(im->isInside(r,k)) // kollar om pixeln vi är innuti, om sant så går vi vidare
    {
        if(colorNew != colorOld)    // om färgen vi vill fylla med är samma som bakgrundfärgen så gör vi inget
        {
            if(im->pixel(r,k) == colorOld)  // om pixeln har den gala färgen så görs rekursionen
            {
                im->setPixel(r,k,colorNew); // sätter pixeln till den nya färgen

                recursiveFill(r, k+1, im, colorOld, colorNew);    // upp
                recursiveFill(r, k-1, im, colorOld, colorNew);    // ner
                recursiveFill(r-1 , k, im, colorOld, colorNew);   // vänster
                recursiveFill(r+1, k, im, colorOld, colorNew);   // höger

            }
        }
    }

}
