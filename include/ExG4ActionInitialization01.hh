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
// $Id: ExG4ActionInitialization01.hh$
//
/// \file ExG4ActionInitialization01.hh
/// \brief Definition of the ExG4ActionInitialization01 class

#ifndef ExG4ActionInitialization01_h
#define ExG4ActionInitialization01_h 1

#include "G4VUserActionInitialization.hh"

/// Обязательный класс, который должен быть объявлен в проекте Geant4
/// Имя класса может быть другим, и он должен наследоваться от
/// класса G4VUserActionInitialization

class ExG4ActionInitialization01 : public G4VUserActionInitialization
{
  public:
    ExG4ActionInitialization01();//Конструктор
    virtual ~ExG4ActionInitialization01();//Деструктор
    virtual void Build() const;//Создание источника первичных частиц

};

#endif
