
#include "studentfill2.h"
#include <QDebug>
#include <deque>   // double-ended-que, har du tillåtelse att använda här!

using namespace std;

// Nedanstående struct kan användas för att lagra koordinater
struct RK {
    RK(int r, int k): _r(r),_k(k) {}
    int _r;
    int _k;
};


// Denna metod visar bara hur man använder en sk deque
void exempelkodDemonstrerarDeque(){

    deque<RK> minQueue;


    qDebug() <<"Demo: vi använder minQueue som en STACK";
    qDebug() <<"      med push_back back och pop_back";

    minQueue.push_back( RK(0,0) );
    minQueue.push_back( RK(1,10) );
    minQueue.push_back( RK(2,20) );

    while (!minQueue.empty()) {
       RK rk = minQueue.back();
       minQueue.pop_back();
       qDebug() << "vi poppar: (" << rk._r << ", " << rk._k << ")";
    }

    qDebug() <<"Demo: vi använder nu minQueue som en FIFO";
    qDebug() <<"      med push_back front och pop_front";

    minQueue.push_back( RK(0,0) );
    minQueue.push_back( RK(1,10) );
    minQueue.push_back( RK(2,20) );

    while (!minQueue.empty()) {
       RK rk = minQueue.front();
       minQueue.pop_front();
       qDebug() << "vi pop_frontar: (" << rk._r << ", " << rk._k << ")";
    }

}



void nonRecursiveFillStack(int r, int k, IDrawingParent *im, QColor colorOld, QColor colorNew){

    // Nedanstående kod är felakrig och skall tas bort
    //exempelkodDemonstrerarDeque();

    deque<RK> minQueue;
    minQueue.push_back( RK(r, k) );

    while(!minQueue.empty())
    {
        RK rk = minQueue.back();
        minQueue.pop_back();

        if(im->isInside(rk._r, rk._k))
        {
            if(colorNew != colorOld)
            {
                if(im->pixel(rk._r, rk._k) == colorOld)
                {
                    im->setPixel(rk._r, rk._k, colorNew);

                    minQueue.push_front( RK(rk._r+1, rk._k) );
                    minQueue.push_front( RK(rk._r-1, rk._k) );
                    minQueue.push_front( RK(rk._r, rk._k+1) );
                    minQueue.push_front( RK(rk._r, rk._k-1) );
                }
            }
        }
    }



}


void nonRecursiveFillFifo(int r, int k, IDrawingParent *im, QColor colorOld, QColor colorNew){
    // Nedanstående kod är felakrig och skall tas bort
    //exempelkodDemonstrerarDeque();
    deque<RK> minQueue;

    minQueue.push_back(RK(r,k));        // startkordinater, ser till att kön inte är tom.

    while(!minQueue.empty())
    {

        RK rk = minQueue.front();   // lagra ny r och k i variabeln rk.
        minQueue.pop_front();

        if(im->isInside(rk._r, rk._k))      // om rk är inne i pappret
        {
            if(colorNew != colorOld)        // om den nya färgen skiljer sig frn den gamla
            {
                if(im->pixel(rk._r,rk._k) == colorOld)  // om pizeln im är samma som gamla färgen
                {
                    im->setPixel(rk._r,rk._k, colorNew);    // måla om pixeln tillny färg

                    minQueue.push_back( RK(rk._r+1, rk._k) );   // lägg in nya r och k i kön.
                    minQueue.push_back( RK(rk._r-1, rk._k) );
                    minQueue.push_back( RK(rk._r, rk._k+1) );
                    minQueue.push_back( RK(rk._r, rk._k-1) );
                }
            }
            // slutet avloopen

        }


    }

}


