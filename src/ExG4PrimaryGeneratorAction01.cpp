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
/// \file ExG4PrimaryGeneratorAction01.cpp
/// \brief Implementation of the ExG4PrimaryGeneratorAction01 class

#include "ExG4PrimaryGeneratorAction01.hh"
// Подключаем необходимы заголовочные файлы
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

// Класс, в котором описывается положение, тип, энергию, направление вылета
// и распределение начальных частиц
ExG4PrimaryGeneratorAction01::ExG4PrimaryGeneratorAction01()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0), 
  fEnvelopeBox(0)
{
  // По умолчанию поставим 1 частицу
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  // Получаем встроеную в Geant4 таблицу частиц
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  // Ищем частицу, в нашем случае протон
  G4ParticleDefinition* particle
    = particleTable->FindParticle(particleName="proton");
  // Устанавливаем полученную частицу в качестве испускаемого типа начальных частиц в источнике
  fParticleGun->SetParticleDefinition(particle);
  // Устанавливаем направление движение частицы по (x,y,z)
  // Здесь устанавливается направление вдоль оси Z
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  // Установка начальной энергии испускаемых частиц, 50 МэВ
  fParticleGun->SetParticleEnergy(50*MeV);
}

// Деструктор
ExG4PrimaryGeneratorAction01::~ExG4PrimaryGeneratorAction01()
{
  // удаляем созданный в конструкторе экземпляр класса источника G4ParticleGun
  delete fParticleGun;
}

void ExG4PrimaryGeneratorAction01::GeneratePrimaries(G4Event* anEvent)
{
  //Эта функция вызывается в начале каждого первичного события запуска частицы
  // Для избежания зависимости этого класса от класса DetectorConstruction,
  // мы получаем ссылку на объем детектора через класс G4LogicalVolumeStore
  
  G4double envSizeXY = 0;
  G4double envSizeZ = 0;
  // Проверяем или ссылка на fEnvelopeBox пустая
  if (!fEnvelopeBox)
  {
     // Если пустая, то получаем ссылку на объем детектора
    G4LogicalVolume* envLV
      = G4LogicalVolumeStore::GetInstance()->GetVolume("Detector");
    if ( envLV ) fEnvelopeBox = dynamic_cast<G4Box*>(envLV->GetSolid());
  }
  // Получаем размеры объема, стороны по x и y предполагается что одинаковы
  if ( fEnvelopeBox ) {
    envSizeXY = fEnvelopeBox->GetXHalfLength()*2.;
    envSizeZ = fEnvelopeBox->GetZHalfLength()*2.;
  }  
  else  {//Если ссылка на fEnvelopeBox пустая, выдаем предупреждение
    G4ExceptionDescription msg;
    msg << "Envelope volume of box shape not found.\n"; 
    msg << "Perhaps you have changed geometry.\n";
    msg << "The gun will be place at the center.";
    G4Exception("B1PrimaryGeneratorAction::GeneratePrimaries()",
     "MyCode0002",JustWarning,msg);
  }
  // Объявляем переменные положения пушки частиц
  G4double x0 = 0;
  G4double y0 = 0;
  G4double z0 = -0.5 * 20*cm;
  // Устанавливаем положение
  fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));
  // Генерируем первичное событие
  fParticleGun->GeneratePrimaryVertex(anEvent);
}
