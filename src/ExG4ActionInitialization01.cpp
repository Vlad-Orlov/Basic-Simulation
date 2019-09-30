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
/// \file ExG4ActionInitialization01.cpp
/// \brief Implementation of the ExG4ActionInitialization01 class
#include "ExG4ActionInitialization01.hh"
#include "ExG4PrimaryGeneratorAction01.hh"//Подключаем обязательный класс
//в котором описываются источник начальных частиц

/// Обязательный класс, который должен быть объявлен в проекте Geant4
/// Имя класса может быть другим, и он должен наследоваться от
/// класса G4VUserActionInitialization

/// Конструктор
ExG4ActionInitialization01::ExG4ActionInitialization01()
 : G4VUserActionInitialization()
{}
//Деструктор, ничего не объявляли, поэтому оставим пустым
ExG4ActionInitialization01::~ExG4ActionInitialization01()
{}
//Создание источника первичных частиц
void ExG4ActionInitialization01::Build() const
{
SetUserAction(new ExG4PrimaryGeneratorAction01);//Задается источник первичных частиц
// через обязательный класс ExG4PrimaryGeneratorAction01
}
