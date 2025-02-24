/********************************************************************************
 * The Peacenet - bit::phoenix("software");
 * 
 * MIT License
 *
 * Copyright (c) 2018-2019 Michael VanOverbeek, Declan Hoare, Ian Clary, 
 * Trey Smith, Richard Moch, Victor Tran and Warren Harris
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 * Contributors:
 *  - Michael VanOverbeek <alkaline@bitphoenixsoftware.com>
 *
 ********************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MissionAsset.h"
#include "MissionActor.generated.h"

class APeacenetWorldStateActor;

UCLASS()
class PROJECTOGLOWIA_API AMissionActor : public AActor
{
    GENERATED_BODY()

public:
    AMissionActor();

private:
    UPROPERTY()
    bool IsFailed = false;

    UPROPERTY()
    TArray<FMissionTaskInfo> LoadedTasks;

    UPROPERTY()
    int CurrentTask = -1;

    UPROPERTY()
    int CheckpointTask = -1;

    UPROPERTY()
    APeacenetWorldStateActor* Peacenet;

    UPROPERTY()
    UMissionAsset* Mission;

public:
    UFUNCTION()
    void Setup(APeacenetWorldStateActor* InPeacenet, UMissionAsset* InMission);

    UFUNCTION()
    APeacenetWorldStateActor* GetPeacenet();

    UFUNCTION()
    void Abort();

    UFUNCTION()
    void SendGameEvent(FString EventName, TMap<FString, FString> InEventData);

public:
    virtual void Tick(float InDeltaSeconds) override;

protected:
    UFUNCTION()
    void Advance();

    UFUNCTION()
    void Complete();

    UFUNCTION()
    void SetCheckpoint();

    UFUNCTION()
    void DeleteSaveStates();

public:
    UFUNCTION()
    UMissionAsset* GetMissionAsset();

    UFUNCTION()
    void FailCurrentTask(const FText& InFailReason);

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Mission")
    bool HasCheckpoint();

    UFUNCTION(BlueprintCallable, Category = "Mission")
    void RestoreCheckpoint();

    UFUNCTION(BlueprintCallable, Category = "Mission")
    void RestartMission();

    UFUNCTION(BlueprintCallable, Category = "Mission")
    void AbandonMission();

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Mission")
    FText GetMissionName();
};