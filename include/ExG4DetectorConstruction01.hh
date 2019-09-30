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
//
/// \file ExG4DetectorConstruction01.hh
/// \brief Definition of the ExG4DetectorConstruction01 class

#ifndef ExG4DetectorConstruction01_h
#define ExG4DetectorConstruction01_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

/// \brief The ExG4DetectorConstruction01 class Класс геометрии установки,
///  объявление материалов и детекторов

class ExG4DetectorConstruction01 : public G4VUserDetectorConstruction
{
  public:
    //Конструктор, вызывается при создании экземпляра класса
    //Обычно используется для задания начальных значений и значений по умолчанию
    //при создании геометрии и материалов
    ExG4DetectorConstruction01();
    //Деструктор, вызывается при удалении экземпляра класса
    //Обычно используется для освобождения памяти инициализированных массивов внутри класса
    virtual ~ExG4DetectorConstruction01();
    //Объявление и создание детекторов и среды
    virtual G4VPhysicalVolume* Construct();
    //Установка чувствительного объема. Когда частица в нем, то в нем извлекается
    //вся информация о треке и параметрах частицы на каждом шаге моделирования
    virtual void ConstructSDandField();
  protected:
};
#endif

