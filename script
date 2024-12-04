local function CreateAdvancedUI(title)
    local ScreenGui = Instance.new("ScreenGui")
    local MainFrame = Instance.new("Frame")
    local TopBar = Instance.new("Frame")
    local TabHolder = Instance.new("Frame")
    local TabContainer = Instance.new("ScrollingFrame")
    local ContentContainer = Instance.new("Frame")
    local Library = {}
    
    -- 전역 변수로 설정 상태 저장
    Library.Settings = {
        Transparency = 0.3,
        UserInfoVisible = true,
        NotificationsEnabled = true,
        CurrentColor = Color3.fromRGB(45, 45, 45),
        DefaultColor = Color3.fromRGB(45, 45, 45)
    }
    
    -- UI 요소들을 저장할 테이블
    Library.Elements = {
        Frames = {},
        Buttons = {},
        Toggles = {}
    }
    
    -- 알림 관리를 위한 테이블
    Library.Notifications = {
        Active = {},
        MaxNotifications = 5
    }
    
    -- ScreenGui 설정
    ScreenGui.Name = "AdvancedUI"
    ScreenGui.Parent = game.Players.LocalPlayer:WaitForChild("PlayerGui")
    ScreenGui.ZIndexBehavior = Enum.ZIndexBehavior.Sibling
    ScreenGui.ResetOnSpawn = false
    
    -- 모서리 둥글게 만드는 함수
    local function AddCorner(instance, radius)
        local corner = Instance.new("UICorner")
        corner.CornerRadius = UDim.new(0, radius or 6)
        corner.Parent = instance
    end
    
    -- 테두리 추가 함수
    local function AddStroke(instance, thickness, color)
        local stroke = Instance.new("UIStroke")
        stroke.Thickness = thickness or 1
        stroke.Color = color or Color3.fromRGB(255, 255, 255)
        stroke.Parent = instance
    end
    
    -- 플로팅 버튼 생성 함수
    local function CreateFloatingButton()
        local floatingButton = Instance.new("TextButton")
        floatingButton.Size = UDim2.new(0, 40, 0, 40)
        floatingButton.Position = UDim2.new(1, -60, 0, 20)
        floatingButton.BackgroundColor3 = Color3.fromRGB(45, 45, 45)
        floatingButton.BackgroundTransparency = 0.1
        floatingButton.Text = "C"
        floatingButton.TextColor3 = Color3.fromRGB(220, 220, 220)
        floatingButton.TextSize = 18
        floatingButton.Font = Enum.Font.Gotham
        floatingButton.Parent = ScreenGui
        AddCorner(floatingButton, 4)
        AddStroke(floatingButton, 1, Color3.fromRGB(255, 255, 255))
        
        -- 드래그 기능
        local dragging = false
        local dragStart = nil
        local startPos = nil
        
        floatingButton.MouseButton1Down:Connect(function()
            dragging = true
            dragStart = game:GetService("UserInputService"):GetMouseLocation()
            startPos = floatingButton.Position
        end)
        
        game:GetService("UserInputService").InputChanged:Connect(function(input)
            if dragging and input.UserInputType == Enum.UserInputType.MouseMovement then
                local delta = game:GetService("UserInputService"):GetMouseLocation() - dragStart
                floatingButton.Position = UDim2.new(
                    startPos.X.Scale,
                    startPos.X.Offset + delta.X,
                    startPos.Y.Scale,
                    startPos.Y.Offset + delta.Y
                )
            end
        end)
        
        game:GetService("UserInputService").InputEnded:Connect(function(input)
            if input.UserInputType == Enum.UserInputType.MouseButton1 then
                dragging = false
            end
        end)
        
        -- 클릭 시 UI 복원
        floatingButton.MouseButton1Click:Connect(function()
            if not dragging then
                minimized = false
                
                -- 플로팅 버튼 페이드 아웃
                game:GetService("TweenService"):Create(floatingButton,
                    TweenInfo.new(0.3, Enum.EasingStyle.Quad),
                    {BackgroundTransparency = 1, TextTransparency = 1}
                ):Play()
                
                wait(0.3)
                floatingButton:Destroy()
                
                -- UI 복원
                MainFrame.Visible = true
                local fadeIn = game:GetService("TweenService"):Create(MainFrame,
                    TweenInfo.new(0.3, Enum.EasingStyle.Quad),
                    {BackgroundTransparency = Library.Settings.Transparency}
                )
                fadeIn:Play()
                
                -- 모든 자식 요소들 페이드 인
                for _, child in ipairs(MainFrame:GetDescendants()) do
                    if child:IsA("Frame") or child:IsA("TextButton") or child:IsA("TextLabel") then
                        game:GetService("TweenService"):Create(child,
                            TweenInfo.new(0.3, Enum.EasingStyle.Quad),
                            {BackgroundTransparency = Library.Settings.Transparency}
                        ):Play()
                        if child:IsA("TextButton") or child:IsA("TextLabel") then
                            game:GetService("TweenService"):Create(child,
                                TweenInfo.new(0.3, Enum.EasingStyle.Quad),
                                {TextTransparency = 0}
                            ):Play()
                        end
                    end
                end
            end
        end)
        
        return floatingButton
    end
    
    -- 알림 생성 함수
    function Library:CreateNotification(text)
        if not Library.Settings.NotificationsEnabled then return end
        
        -- 새로운 알림 위치 계산
        local yOffset = 60 + (#Library.Notifications.Active * 55)
        
        -- 기존 알림들을 위로 이동
        for _, notif in ipairs(Library.Notifications.Active) do
            local newPosition = UDim2.new(1, -220, 1, -(notif.YOffset + 55))
            local tween = game:GetService("TweenService"):Create(notif.Frame, 
                TweenInfo.new(0.3, Enum.EasingStyle.Quad), 
                {Position = newPosition}
            )
            tween:Play()
            notif.YOffset = notif.YOffset + 55
        end
        
        -- 새 알림 생성
        local notification = Instance.new("Frame")
        notification.Size = UDim2.new(0, 200, 0, 50)
        notification.Position = UDim2.new(1, 0, 1, -yOffset)
        notification.BackgroundColor3 = Color3.fromRGB(50, 50, 50)
        notification.BackgroundTransparency = 0.1
        notification.Parent = ScreenGui
        AddCorner(notification, 6)
        AddStroke(notification, 1, Color3.fromRGB(255, 255, 255))
        
        local notificationText = Instance.new("TextLabel")
        notificationText.Size = UDim2.new(1, -10, 1, 0)
        notificationText.Position = UDim2.new(0, 5, 0, 0)
        notificationText.BackgroundTransparency = 1
        notificationText.Text = text
        notificationText.TextColor3 = Color3.fromRGB(220, 220, 220)
        notificationText.TextSize = 14
        notificationText.Font = Enum.Font.Gotham
        notificationText.Parent = notification
        
        -- 알림 슬라이드 인 애니메이션
        local tween = game:GetService("TweenService"):Create(notification, 
            TweenInfo.new(0.3, Enum.EasingStyle.Quad), 
            {Position = UDim2.new(1, -220, 1, -yOffset)}
        )
        tween:Play()
        
        -- 알림 정보 저장
        local notifData = {
            Frame = notification,
            YOffset = yOffset
        }
        table.insert(Library.Notifications.Active, notifData)
        
        -- 최대 알림 개수 초과시 가장 오래된 알림 제거
        if #Library.Notifications.Active > Library.Notifications.MaxNotifications then
            local oldestNotif = table.remove(Library.Notifications.Active, 1)
            local fadeOut = game:GetService("TweenService"):Create(oldestNotif.Frame, 
                TweenInfo.new(0.3, Enum.EasingStyle.Quad), 
                {Position = UDim2.new(1, 0, 1, -oldestNotif.YOffset)}
            )
            fadeOut:Play()
            fadeOut.Completed:Connect(function()
                oldestNotif.Frame:Destroy()
            end)
        end
        
        -- 3초 후 알림 제거
        delay(3, function()
            -- 알림 목록에서 제거
            for i, notif in ipairs(Library.Notifications.Active) do
                if notif.Frame == notification then
                    table.remove(Library.Notifications.Active, i)
                    break
                end
            end
            
            -- 페이드 아웃 애니메이션
            local fadeOut = game:GetService("TweenService"):Create(notification, 
                TweenInfo.new(0.3, Enum.EasingStyle.Quad), 
                {Position = UDim2.new(1, 0, 1, -yOffset)}
            )
            fadeOut:Play()
            fadeOut.Completed:Connect(function()
                notification:Destroy()
            end)
        end)
    end
    
    -- MainFrame 설정
    MainFrame.Name = "MainFrame"
    MainFrame.Size = UDim2.new(0, 700, 0, 450)
    MainFrame.Position = UDim2.new(0.5, -350, 0.5, -225)
    MainFrame.BackgroundColor3 = Library.Settings.CurrentColor
    MainFrame.BackgroundTransparency = Library.Settings.Transparency
    MainFrame.Parent = ScreenGui
    AddCorner(MainFrame, 8)
    AddStroke(MainFrame, 1)
    
    -- TopBar 설정
    TopBar.Name = "TopBar"
    TopBar.Size = UDim2.new(1, 0, 0, 30)
    TopBar.BackgroundColor3 = Color3.fromRGB(40, 40, 40)
    TopBar.BackgroundTransparency = Library.Settings.Transparency
    TopBar.Parent = MainFrame
    AddCorner(TopBar, 8)
    AddStroke(TopBar, 1)
    
    -- 타이틀 설정
    local TitleLabel = Instance.new("TextLabel")
    TitleLabel.Size = UDim2.new(0.5, 0, 1, 0)
    TitleLabel.Position = UDim2.new(0, 10, 0, 0)
    TitleLabel.BackgroundTransparency = 1
    TitleLabel.Text = title or "Advanced UI"
    TitleLabel.TextColor3 = Color3.fromRGB(220, 220, 220)
    TitleLabel.TextSize = 14
    TitleLabel.Font = Enum.Font.Gotham
    TitleLabel.TextXAlignment = Enum.TextXAlignment.Left
    TitleLabel.Parent = TopBar
    
    -- 닫기/최소화 버튼
    local CloseButton = Instance.new("TextButton")
    CloseButton.Size = UDim2.new(0, 30, 0, 20)
    CloseButton.Position = UDim2.new(1, -35, 0, 5)
    CloseButton.BackgroundColor3 = Color3.fromRGB(255, 100, 100)
    CloseButton.BackgroundTransparency = 0.1
    CloseButton.Text = "X"
    CloseButton.TextColor3 = Color3.fromRGB(220, 220, 220)
    CloseButton.TextSize = 14
    CloseButton.Font = Enum.Font.Gotham
    CloseButton.Parent = TopBar
    AddCorner(CloseButton, 4)
    AddStroke(CloseButton, 1)
    
    local MinimizeButton = Instance.new("TextButton")
    MinimizeButton.Size = UDim2.new(0, 30, 0, 20)
    MinimizeButton.Position = UDim2.new(1, -70, 0, 5)
    MinimizeButton.BackgroundColor3 = Color3.fromRGB(100, 100, 255)
    MinimizeButton.BackgroundTransparency = 0.1
    MinimizeButton.Text = "-"
    MinimizeButton.TextColor3 = Color3.fromRGB(220, 220, 220)
    MinimizeButton.TextSize = 14
    MinimizeButton.Font = Enum.Font.Gotham
    MinimizeButton.Parent = TopBar
    AddCorner(MinimizeButton, 4)
    AddStroke(MinimizeButton, 1)
    
    -- TabHolder 설정
    TabHolder.Name = "TabHolder"
    TabHolder.Size = UDim2.new(0, 150, 1, -35)
    TabHolder.Position = UDim2.new(0, 5, 0, 35)
    TabHolder.BackgroundColor3 = Color3.fromRGB(35, 35, 35)
    TabHolder.BackgroundTransparency = Library.Settings.Transparency
    TabHolder.Parent = MainFrame
    AddCorner(TabHolder, 6)
    AddStroke(TabHolder, 1)
    
    -- TabContainer 설정
    TabContainer.Name = "TabContainer"
    TabContainer.Size = UDim2.new(1, -10, 1, -120)
    TabContainer.Position = UDim2.new(0, 5, 0, 5)
    TabContainer.BackgroundTransparency = 1
    TabContainer.ScrollBarThickness = 2
    TabContainer.Parent = TabHolder
    
    local TabListLayout = Instance.new("UIListLayout")
    TabListLayout.Parent = TabContainer
    TabListLayout.Padding = UDim.new(0, 5)
    TabListLayout.HorizontalAlignment = Enum.HorizontalAlignment.Center
    
    -- ContentContainer 설정
    ContentContainer.Name = "ContentContainer"
    ContentContainer.Size = UDim2.new(1, -160, 1, -35)
    ContentContainer.Position = UDim2.new(0, 155, 0, 35)
    ContentContainer.BackgroundColor3 = Color3.fromRGB(25, 25, 25)
    ContentContainer.BackgroundTransparency = Library.Settings.Transparency
    ContentContainer.Parent = MainFrame
    AddCorner(ContentContainer, 6)
    AddStroke(ContentContainer, 1)
    
    -- UserInfo 생성
    local function CreateUserInfo()
        local UserInfoFrame = Instance.new("Frame")
        UserInfoFrame.Name = "UserInfoFrame"
        UserInfoFrame.Size = UDim2.new(1, -10, 0, 120)
        UserInfoFrame.Position = UDim2.new(0, 5, 1, -125)
        UserInfoFrame.BackgroundColor3 = Color3.fromRGB(35, 35, 35)
        UserInfoFrame.BackgroundTransparency = Library.Settings.Transparency
        UserInfoFrame.Parent = TabHolder
        AddCorner(UserInfoFrame, 6)
        AddStroke(UserInfoFrame, 1)
        
        local ProfileImage = Instance.new("ImageLabel")
        ProfileImage.Size = UDim2.new(0, 70, 0, 70)
        ProfileImage.Position = UDim2.new(0.5, -35, 0, 5)
        ProfileImage.BackgroundColor3 = Color3.fromRGB(30, 30, 30)
        ProfileImage.Image = game.Players:GetUserThumbnailAsync(
            game.Players.LocalPlayer.UserId,
            Enum.ThumbnailType.HeadShot,
            Enum.ThumbnailSize.Size100x100
        )
        ProfileImage.Parent = UserInfoFrame
        AddCorner(ProfileImage, 35)
        
        local Username = Instance.new("TextLabel")
        Username.Size = UDim2.new(1, -10, 0, 20)
        Username.Position = UDim2.new(0, 5, 0, 80)
        Username.BackgroundTransparency = 1
        Username.Text = game.Players.LocalPlayer.Name
        Username.TextColor3 = Color3.fromRGB(220, 220, 220)
        Username.TextSize = 14
        Username.Font = Enum.Font.Gotham
        Username.Parent = UserInfoFrame
        
        local UserStatus = Instance.new("TextLabel")
        UserStatus.Size = UDim2.new(1, -10, 0, 20)
        UserStatus.Position = UDim2.new(0, 5, 0, 95)
        UserStatus.BackgroundTransparency = 1
        UserStatus.Text = "VIP 유저"
        UserStatus.TextColor3 = Color3.fromRGB(220, 220, 220)
        UserStatus.TextSize = 14
        UserStatus.Font = Enum.Font.Gotham
        UserStatus.Parent = UserInfoFrame
        
        Library.UserInfoFrame = UserInfoFrame
    end
    
    CreateUserInfo()
    
    -- 드래그 기능
    local UserInputService = game:GetService("UserInputService")
    local dragging
    local dragInput
    local dragStart
    local startPos
    
    local function update(input)
        local delta = input.Position - dragStart
        MainFrame.Position = UDim2.new(startPos.X.Scale, startPos.X.Offset + delta.X,
            startPos.Y.Scale, startPos.Y.Offset + delta.Y)
    end
    
    TopBar.InputBegan:Connect(function(input)
        if input.UserInputType == Enum.UserInputType.MouseButton1 then
            dragging = true
            dragStart = input.Position
            startPos = MainFrame.Position
        end
    end)
    
    TopBar.InputEnded:Connect(function(input)
        if input.UserInputType == Enum.UserInputType.MouseButton1 then
            dragging = false
        end
    end)
    
    UserInputService.InputChanged:Connect(function(input)
        if dragging and input.UserInputType == Enum.UserInputType.MouseMovement then
            update(input)
        end
    end)
    
    -- 닫기/최소화 기능
    CloseButton.MouseButton1Click:Connect(function()
        ScreenGui:Destroy()
    end)
    
    local minimized = false
    MinimizeButton.MouseButton1Click:Connect(function()
        minimized = not minimized
        
        if minimized then
            -- UI 페이드 아웃
            local fadeOut = game:GetService("TweenService"):Create(MainFrame, 
                TweenInfo.new(0.3, Enum.EasingStyle.Quad), 
                {BackgroundTransparency = 1}
            )
            fadeOut:Play()
            
            -- 모든 자식 요소들 페이드 아웃
            for _, child in ipairs(MainFrame:GetDescendants()) do
                if child:IsA("Frame") or child:IsA("TextButton") or child:IsA("TextLabel") then
                    game:GetService("TweenService"):Create(child,
                        TweenInfo.new(0.3, Enum.EasingStyle.Quad),
                        {BackgroundTransparency = 1}
                    ):Play()
                    if child:IsA("TextButton") or child:IsA("TextLabel") then
                        game:GetService("TweenService"):Create(child,
                            TweenInfo.new(0.3, Enum.EasingStyle.Quad),
                            {TextTransparency = 1}
                        ):Play()
                    end
                end
            end
            
            -- 페이드 아웃 완료 후 UI 숨기기
            wait(0.3)
            MainFrame.Visible = false
            
            -- 플로팅 버튼 생성
            floatingButton = CreateFloatingButton()
            
            -- 플로팅 버튼 페이드 인
            floatingButton.BackgroundTransparency = 1
            floatingButton.TextTransparency = 1
            game:GetService("TweenService"):Create(floatingButton,
                TweenInfo.new(0.3, Enum.EasingStyle.Quad),
                {BackgroundTransparency = 0.1, TextTransparency = 0}
            ):Play()
        else
            -- 플로팅 버튼 페이드 아웃 후 제거
            game:GetService("TweenService"):Create(floatingButton,
                TweenInfo.new(0.3, Enum.EasingStyle.Quad),
                {BackgroundTransparency = 1, TextTransparency = 1}
            ):Play()
            wait(0.3)
            floatingButton:Destroy()
            
            -- UI 다시 표시
            MainFrame.Visible = true
            MainFrame.BackgroundTransparency = 1
            
            -- UI 페이드 인
            local fadeIn = game:GetService("TweenService"):Create(MainFrame,
                TweenInfo.new(0.3, Enum.EasingStyle.Quad),
                {BackgroundTransparency = Library.Settings.Transparency}
            )
            fadeIn:Play()
            
            -- 모든 자식 요소들 페이드 인
            for _, child in ipairs(MainFrame:GetDescendants()) do
                if child:IsA("Frame") or child:IsA("TextButton") or child:IsA("TextLabel") then
                    game:GetService("TweenService"):Create(child,
                        TweenInfo.new(0.3, Enum.EasingStyle.Quad),
                        {BackgroundTransparency = Library.Settings.Transparency}
                    ):Play()
                    if child:IsA("TextButton") or child:IsA("TextLabel") then
                        game:GetService("TweenService"):Create(child,
                            TweenInfo.new(0.3, Enum.EasingStyle.Quad),
                            {TextTransparency = 0}
                        ):Play()
                    end
                end
            end
        end
    end)
    
    -- 탭 생성 함수
    function Library:CreateTab(name)
        local tab = {}
        
        local tabButton = Instance.new("TextButton")
        tabButton.Size = UDim2.new(0.9, 0, 0, 35)
        tabButton.BackgroundColor3 = Color3.fromRGB(40, 40, 40)
        tabButton.BackgroundTransparency = Library.Settings.Transparency
        tabButton.Text = name
        tabButton.TextColor3 = Color3.fromRGB(220, 220, 220)
        tabButton.TextSize = 20
        tabButton.Font = Enum.Font.Gotham
        tabButton.Parent = TabContainer
        AddCorner(tabButton, 6)
        AddStroke(tabButton, 1)
        
        local tabContent = Instance.new("ScrollingFrame")
        tabContent.Size = UDim2.new(1, -10, 1, -10)
        tabContent.Position = UDim2.new(0, 5, 0, 5)
        tabContent.BackgroundTransparency = 1
        tabContent.ScrollBarThickness = 2
        tabContent.Visible = false
        tabContent.Parent = ContentContainer
        
        local contentLayout = Instance.new("UIListLayout")
        contentLayout.Parent = tabContent
        contentLayout.Padding = UDim.new(0, 5)
        contentLayout.HorizontalAlignment = Enum.HorizontalAlignment.Center
        
        tabButton.MouseButton1Click:Connect(function()
            for _, v in pairs(ContentContainer:GetChildren()) do
                if v:IsA("ScrollingFrame") then
                    v.Visible = false
                end
            end
            tabContent.Visible = true
        end)
        
        function tab:CreateButton(text, callback)
            local button = Instance.new("TextButton")
            button.Size = UDim2.new(0.9, 0, 0, 35)
            button.BackgroundColor3 = Color3.fromRGB(45, 45, 45)
            button.BackgroundTransparency = Library.Settings.Transparency
            button.Text = text
            button.TextColor3 = Color3.fromRGB(220, 220, 220)
            button.TextSize = 18
            button.Font = Enum.Font.Gotham
            button.Parent = tabContent
            AddCorner(button, 6)
            AddStroke(button, 1)
            
            button.MouseButton1Click:Connect(function()
                callback()
                Library:CreateNotification(text .. " 버튼이 클릭되었습니다")
            end)
            return button
        end
        
        function tab:CreateToggle(text, callback)
            local toggleFrame = Instance.new("Frame")
            toggleFrame.Size = UDim2.new(0.9, 0, 0, 35)
            toggleFrame.BackgroundColor3 = Color3.fromRGB(45, 45, 45)
            toggleFrame.BackgroundTransparency = Library.Settings.Transparency
            toggleFrame.Parent = tabContent
            AddCorner(toggleFrame, 6)
            AddStroke(toggleFrame, 1)
            
            local toggleButton = Instance.new("TextButton")
            toggleButton.Size = UDim2.new(0, 25, 0, 25)
            toggleButton.Position = UDim2.new(0, 5, 0.5, -12)
            toggleButton.BackgroundColor3 = Color3.fromRGB(255, 70, 70)
            toggleButton.BackgroundTransparency = 0.1
            toggleButton.Text = ""
            toggleButton.Parent = toggleFrame
            AddCorner(toggleButton, 4)
            AddStroke(toggleButton, 1)
            
            local toggleText = Instance.new("TextLabel")
            toggleText.Size = UDim2.new(1, -40, 1, 0)
            toggleText.Position = UDim2.new(0, 35, 0, 0)
            toggleText.BackgroundTransparency = 1
            toggleText.Text = text
            toggleText.TextColor3 = Color3.fromRGB(220, 220, 220)
            toggleText.TextSize = 18
            toggleText.Font = Enum.Font.Gotham
            toggleText.TextXAlignment = Enum.TextXAlignment.Left
            toggleText.Parent = toggleFrame
            
            local toggled = false
            toggleButton.MouseButton1Click:Connect(function()
                toggled = not toggled
                toggleButton.BackgroundColor3 = toggled and Color3.fromRGB(70, 255, 70) or Color3.fromRGB(255, 70, 70)
                callback(toggled)
            end)
            
            return toggleFrame, toggleButton
        end
        
        -- 메시지 생성 함수
        function tab:CreateMessage(text)
            local messageFrame = Instance.new("Frame")
            messageFrame.Size = UDim2.new(0.9, 0, 0, 35)
            messageFrame.BackgroundColor3 = Color3.fromRGB(45, 45, 45)
            messageFrame.BackgroundTransparency = Library.Settings.Transparency
            messageFrame.Parent = tabContent
            AddCorner(messageFrame, 6)
            AddStroke(messageFrame, 1)
            
            local messageText = Instance.new("TextLabel")
            messageText.Size = UDim2.new(1, -10, 1, 0)
            messageText.Position = UDim2.new(0, 5, 0, 0)
            messageText.BackgroundTransparency = 1
            messageText.Text = text
            messageText.TextColor3 = Color3.fromRGB(220, 220, 220)
            messageText.TextSize = 14
            messageText.Font = Enum.Font.Gotham
            messageText.TextXAlignment = Enum.TextXAlignment.Left
            messageText.Parent = messageFrame
            
            return messageFrame
        end
        
        tab.Container = tabContent
        return tab
    end
    
    -- 설정 탭 생성
    local SettingsTab = Library:CreateTab("설정")
    
    -- 반투명도 토글
    local _, transparencyToggle = SettingsTab:CreateToggle("반투명 효과", function(state)
        Library:UpdateTransparency(state and 0.3 or 0.1)
    end)
    Library.Elements.Toggles.Transparency = transparencyToggle
    transparencyToggle.BackgroundColor3 = Color3.fromRGB(70, 255, 70)
    
    -- 유저 정보 토글
    local _, userInfoToggle = SettingsTab:CreateToggle("유저 정보 표시", function(state)
        Library:UpdateUserInfoVisibility(state)
    end)
    Library.Elements.Toggles.UserInfo = userInfoToggle
    userInfoToggle.BackgroundColor3 = Color3.fromRGB(70, 255, 70)
    
    -- 알림 토글
    local _, notificationToggle = SettingsTab:CreateToggle("알림 표시", function(state)
        Library.Settings.NotificationsEnabled = state
        -- 테스트 알림 표시
        if state then
            Library:CreateNotification("알림이 활성화되었습니다")
        end
    end)
    Library.Elements.Toggles.Notification = notificationToggle
    notificationToggle.BackgroundColor3 = Color3.fromRGB(70, 255, 70)  -- 기본값 ON
    
    -- UI 색상 변경
    local function CreateColorButton(color, text, parent)
        local button = Instance.new("TextButton")
        button.Size = UDim2.new(0.9, 0, 0, 35)
        button.BackgroundColor3 = color
        button.BackgroundTransparency = 0.1
        button.Text = text
        button.TextColor3 = Color3.fromRGB(220, 220, 220)
        button.TextSize = 18
        button.Font = Enum.Font.Gotham
        button.Parent = parent
        AddCorner(button, 6)
        AddStroke(button, 1)
        
        button.MouseButton1Click:Connect(function()
            Library:UpdateColor(color)
        end)
        
        return button
    end
    
    local colorLabel = Instance.new("TextLabel")
    colorLabel.Size = UDim2.new(0.9, 0, 0, 35)
    colorLabel.BackgroundTransparency = 1
    colorLabel.Text = "UI 색상"
    colorLabel.TextColor3 = Color3.fromRGB(220, 220, 220)
    colorLabel.TextSize = 18
    colorLabel.Font = Enum.Font.Gotham
    colorLabel.Parent = SettingsTab.Container
    
    CreateColorButton(Color3.fromRGB(45, 45, 45), "기본", SettingsTab.Container)
    CreateColorButton(Color3.fromRGB(255, 100, 100), "빨간색", SettingsTab.Container)
    CreateColorButton(Color3.fromRGB(100, 100, 255), "파란색", SettingsTab.Container)
    CreateColorButton(Color3.fromRGB(100, 255, 100), "초록색", SettingsTab.Container)
    CreateColorButton(Color3.fromRGB(170, 100, 255), "보라색", SettingsTab.Container)
    
    -- 초기화 버튼
    SettingsTab:CreateButton("설정 초기화", function()
        Library:ResetSettings()
    end)
    
    -- 첫 번째 탭 보이기
    for _, v in pairs(ContentContainer:GetChildren()) do
        if v:IsA("ScrollingFrame") then
            v.Visible = true
            break
        end
    end
    
    return Library
end
