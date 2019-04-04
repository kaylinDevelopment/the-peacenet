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
#include "MissionTask.generated.h"

class AMissionActor;
class APeacenetWorldStateActor;
class UUserContext;

UCLASS(Blueprintable, BlueprintType, Abstract, EditInlineNew)
class PROJECTOGLOWIA_API UMissionTask : public UObject
{
    GENERATED_BODY()

private:
    UPROPERTY()
    AMissionActor* Mission;

    UPROPERTY()
    bool IsFinished = false;

protected:
    virtual void NativeStart() {}
    virtual void NativeTick(float InDeltaSeconds) {}
    virtual void NativeEvent(FString EventName, TMap<FString, FString> InEventArgs) {}

    UFUNCTION(BlueprintCallable, BlueprintPure)
    APeacenetWorldStateActor* GetPeacenet();

    UFUNCTION(BlueprintCallable, BlueprintPure)
    UUserContext* GetPlayerUser();

    UFUNCTION(BlueprintCallable)
    void Complete();

    UFUNCTION(BlueprintImplementableEvent)
    void OnStart();

    UFUNCTION(BlueprintImplementableEvent)
    void OnTick(float InDeltaSeconds);

    UFUNCTION(BlueprintImplementableEvent)
    void OnHandleEvent(const FString& EventName, const TMap<FString, FString>& InEventArgs);

public:
    UFUNCTION()
    void HandleEvent(FString EventName, TMap<FString, FString> InEventArgs);

    UFUNCTION()
    void Start(AMissionActor* InMission);

    UFUNCTION()
    void Tick(float InDeltaSeconds);

    UFUNCTION()
    bool GetIsFinished();
};