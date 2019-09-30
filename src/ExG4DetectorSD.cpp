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
#include<G4Step.hh>
#include<fstream>
#include<iostream>
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "ExG4DetectorSD.hh"
// Используем пространство имен std, что бы не писать много где std::
using namespace std;
// Конструктор чувствительной области, по умолчанию инициализируем нижнюю и верхнюю
// границы гистограммы в 0 и 50 МэВ
ExG4DetectorSD::ExG4DetectorSD(G4String name): G4VSensitiveDetector(name),
                             HIST_MAX(50*MeV),// Инициализация верхней границы
                             HIST_MIN(0 *MeV)// Инициализация нижней границы
{
  // Обнуляем гистограммы
  for(int i = 0; i<NOBINS; i++){
    histogram[i] = 0;
    histogram_angle[i] = 0;
  }
}
//Вызывается на каждом шаге моделирования частицы, когда она попадает в этот чувствительный объем
G4bool ExG4DetectorSD::ProcessHits(G4Step* step, G4TouchableHistory* history)
   {
    // Получаем кинетическую энергии частицы с предыдущего шага, т.е. начальную
    // кинетическую энегрию перед текущим шагом
    double energy = step->GetPreStepPoint()->GetKineticEnergy();
    // Вычисляем ширину бина (интерва) гистограммы
    double bin_width = (HIST_MAX - HIST_MIN) / NOBINS;
    // Если имя частицы протон (proton), тогда заполняем гистограммы
    if(step->GetTrack()->GetDefinition()->GetParticleName() == "proton" ){
         // Определяем индекс (номер) бина гистограммы энергии
         int index = int(floor((energy-HIST_MIN)/bin_width));
         // Добавляем +1 в соответствующий бин
         if(index >= 0 && index < NOBINS)
           histogram[index]++;
         // Далее заполняем гистограмму углового распределения
         // Получаем вектор направления частицы
         G4ThreeVector ang = step->GetPreStepPoint()->GetMomentumDirection();
         // Задаем единичный вектор в направлении оси OZ
         G4ThreeVector *centerVector = new G4ThreeVector(0, 0, 1);
         // Применяем фунцию класса G4ThreeVector - находим угол относительно
         // вектора centerVector
         double angle=ang.angle(*centerVector);
         // Определяем ширину бина в гистограмме углового распределения.
         // Так как у нас измеряются углы между векторами, то максимальный
         // угол равен пи 3.14, минимальный 0
         double bin_width_ang = (3.14) / NOBINS;
         // Получаем номер бина
         index = int(floor((angle)/bin_width_ang));
         // Заполняем гистограмму
         if(index >= 0 && index < NOBINS)
             histogram_angle[index]++;
}
     // Так как мы хотим только измерить параметры частиц после прохождения
     // мишени и не интересуемся дальнейшей их судьбой в детекторе, то их убиваем -
     // устанавливаем статус остановлено и уничтожено (fStopAndKill)
     step->GetTrack()->SetTrackStatus(fStopAndKill);
     return true;
   }
ExG4DetectorSD::~ExG4DetectorSD()
{
    // В деструкторе выводим гистограммы в файлы
    // Открываем файл (существующий файл полностью перезаписывается)
    std::ofstream file("spectrum.dat");
    // Вычисляем ширину бина
    double bin_width = (HIST_MAX - HIST_MIN) / NOBINS;
    // Выводим гистограмму
    for(int i = 0; i<NOBINS; i++)
    {
        // Вычисляем энергию
        double energy = i*bin_width + HIST_MIN;
        // Выводим в файл
        file << std::setw(15) << energy/MeV << " "
             << std::setw(15) << histogram[i] << std::endl;
    }
    // Закрываем файл
    file.close();
    // Открываем файл для вывода гистограммы углового распределения
    file.open("angle.dat");
    // Вычисляем ширину бина
    bin_width = (3.14) / NOBINS;
    // Выводим гистограмму
    for(int i = 0; i<NOBINS; i++)
    {
        // Вычисляем угол
        double angle = i*bin_width;
        // Выводим в файл
        file << std::setw(15) << angle << " "
             << std::setw(15) << histogram_angle[i] << std::endl;
    }
    // Закрываем файл
    file.close();
}
