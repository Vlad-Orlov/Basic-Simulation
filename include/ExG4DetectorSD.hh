// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes, nor the agencies providing financial support for this*
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// *                                                                  *
// * Разработано специально для dev.asifmoda.com                      *
// * Можно использовать для обучения, частных и коммерческих проектов.*
// * Прывітанне з Беларусі!                                           *
// * Автор, идея и реализация:                                        *
// * Виктор Гавриловец, bycel@tut.by,                                 *
// ********************************************************************
#include<G4VSensitiveDetector.hh>
#ifndef ExG4DetectorSD_h
#define ExG4DetectorSD_h 1
   class G4Step;
   class G4TouchableHistory;
   /// Класс определения чувствительной области детектора
   class ExG4DetectorSD: public G4VSensitiveDetector
     {
     private:
       //Создадим гистограмму в которую запишем распределение
       //энергии протонов
       //Число бинов (интервалов в гистограмме)
       static const int NOBINS = 1000;
       //Максимальная энергия в гистограмме
       const double HIST_MAX;
       //Минимальная энергия в гистограмме
       const double HIST_MIN;
       //Объявляем саму гистограмму
       int histogram[NOBINS];
       //Постоим также угол, на который рассеялся протон
       int histogram_angle[NOBINS];
     public:
       //Контструктора, в нем обнуляем гистограммы
        ExG4DetectorSD(G4String name);
        //Декструктор, в нем выведем гистограммы в файл
        //Вывод данных в файл лучше делать здесь чем в ProcessHits, так как
        //вызов деструктора происходит в конце работы программы,
        //а если записывать в процессе моделирования, то значительное
        //время будет тратится на ожидание записи в файл. А это относительно
        //медленная процедура и занимает много времени и в результате
        //моделирование будет занимать больше времени чем нужно.
        ~ExG4DetectorSD();
        //Когда частица попадает в этот чувствительный объем, тогда на каждом
        //её шаге моделирования вызывается эта функция.
        //В ней мы можем получить и передать информацию о состоянии
        //частицы, и ее треке
        G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
     };
#endif /* SENSITIVEDETECTOR */
