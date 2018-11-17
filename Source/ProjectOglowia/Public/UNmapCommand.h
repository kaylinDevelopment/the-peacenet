// Copyright (c) 2018 The Peacenet & Alkaline Thunder.

#pragma once

#include "CoreMinimal.h"
#include "TerminalCommand.h"
#include "USystemContext.h"
#include "PeacenetWorldStateActor.h"
#include "DocoptForUnrealBPLibrary.h"
#include "UNmapCommand.generated.h"

/**
 * A Terminal Command that maps out the services running on a Peacenet computer/network.
 */
UCLASS(BlueprintType)
class PROJECTOGLOWIA_API UNmapCommand : public UTerminalCommand
{
	GENERATED_BODY()

public:
	virtual void RunCommand(UConsoleContext* InConsole, const TMap<FString, UDocoptValue*> InArguments) override;
};