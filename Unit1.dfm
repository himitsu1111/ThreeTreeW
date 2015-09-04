object Form1: TForm1
  Left = 0
  Top = 0
  Caption = #1057#1052#1058#1057' '#1089#1090#1072#1085#1082#1086#1074' '#1089' '#1063#1055#1059
  ClientHeight = 822
  ClientWidth = 1083
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object TreeView2: TTreeView
    Left = 0
    Top = 368
    Width = 275
    Height = 219
    Indent = 19
    PopupMenu = PopupMenu2
    TabOrder = 1
    OnMouseDown = TreeView2MouseDown
  end
  object TreeView1: TTreeView
    Left = 0
    Top = 39
    Width = 275
    Height = 297
    Indent = 19
    PopupMenu = PopupMenu1
    ReadOnly = True
    TabOrder = 0
    OnKeyPress = TreeView1KeyPress
    OnMouseDown = TreeView1MouseDown
    Items.NodeData = {
      01010000002D0000000000000000000000FFFFFFFFFFFFFFFF00000000010000
      000A220435044504200011044E0440043E042000310029000000000000000000
      0000FFFFFFFFFFFFFFFF00000000010000000826043504450420003200310031
      003300250000000000000000000000FFFFFFFFFFFFFFFF000000000100000006
      44004D004300360030005400250000000000000000000000FFFFFFFFFFFFFFFF
      000000000000000006300031003100390036003500}
  end
  object Panel1: TPanel
    Left = 0
    Top = 39
    Width = 275
    Height = 297
    TabOrder = 5
    Visible = False
    object GroupBox1: TGroupBox
      Left = 16
      Top = 34
      Width = 241
      Height = 225
      TabOrder = 0
      object EditTB: TEdit
        Left = 88
        Top = 16
        Width = 137
        Height = 21
        Enabled = False
        TabOrder = 0
      end
      object ComboBox1: TComboBox
        Left = 88
        Top = 16
        Width = 137
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        TabOrder = 10
        Visible = False
      end
      object EditModel: TEdit
        Left = 88
        Top = 60
        Width = 137
        Height = 21
        Enabled = False
        TabOrder = 1
      end
      object EditType: TEdit
        Left = 88
        Top = 108
        Width = 137
        Height = 21
        Enabled = False
        TabOrder = 2
      end
      object EditCeh: TEdit
        Left = 88
        Top = 148
        Width = 137
        Height = 21
        Enabled = False
        TabOrder = 3
      end
      object EditInv: TEdit
        Left = 88
        Top = 188
        Width = 137
        Height = 21
        Enabled = False
        TabOrder = 4
      end
      object StaticText1TB: TStaticText
        Left = 20
        Top = 16
        Width = 56
        Height = 17
        Caption = #1058#1077#1093'. '#1073#1102#1088#1086
        Color = clBtnFace
        ParentColor = False
        TabOrder = 5
        Transparent = False
      end
      object StaticText3Type: TStaticText
        Left = 20
        Top = 108
        Width = 62
        Height = 17
        Caption = #1058#1080#1087' '#1084#1086#1076#1077#1083#1080
        TabOrder = 6
        Transparent = False
      end
      object StaticText2Model: TStaticText
        Left = 20
        Top = 64
        Width = 43
        Height = 17
        Caption = #1052#1086#1076#1077#1083#1100
        TabOrder = 7
        Transparent = False
      end
      object StaticText4Ceh: TStaticText
        Left = 20
        Top = 152
        Width = 24
        Height = 17
        Caption = #1062#1077#1093
        TabOrder = 8
        Transparent = False
      end
      object StaticText5INV: TStaticText
        Left = 20
        Top = 192
        Width = 43
        Height = 17
        Caption = #1048#1085#1074'. '#8470
        TabOrder = 9
        Transparent = False
      end
    end
    object Button3: TButton
      Left = 16
      Top = 263
      Width = 98
      Height = 25
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100
      TabOrder = 1
      OnClick = Button3Click
    end
    object Panel2: TPanel
      Left = 16
      Top = 6
      Width = 241
      Height = 25
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
    end
    object Button4: TButton
      Left = 152
      Top = 263
      Width = 75
      Height = 25
      Caption = #1054#1090#1084#1077#1085#1072
      TabOrder = 3
      OnClick = Button4Click
    end
  end
  object TreeView3: TTreeView
    Left = 281
    Top = 39
    Width = 336
    Height = 548
    Indent = 19
    TabOrder = 2
  end
  object Button1: TButton
    Left = 144
    Top = 8
    Width = 131
    Height = 25
    Caption = #1055#1086' '#1084#1086#1076#1077#1083#1103#1084
    TabOrder = 3
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 0
    Top = 8
    Width = 131
    Height = 25
    Caption = #1055#1086' '#1088#1072#1089#1087#1086#1083#1086#1078#1077#1085#1080#1102
    TabOrder = 4
    OnClick = Button2Click
  end
  object Edit1: TEdit
    Left = 623
    Top = 168
    Width = 121
    Height = 21
    TabOrder = 7
    Text = 'Edit1'
  end
  object Button7: TButton
    Left = 344
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Button7'
    TabOrder = 8
    OnClick = Button7Click
  end
  object Memo1: TMemo
    Left = 623
    Top = 195
    Width = 185
    Height = 89
    Lines.Strings = (
      'Memo1')
    TabOrder = 9
  end
  object TreeView4: TTreeView
    Left = 832
    Top = 39
    Width = 209
    Height = 226
    Indent = 19
    TabOrder = 10
  end
  object TreeView5: TTreeView
    Left = 832
    Top = 320
    Width = 209
    Height = 267
    Indent = 19
    TabOrder = 11
  end
  object Panel3: TPanel
    Left = 0
    Top = 346
    Width = 275
    Height = 241
    TabOrder = 6
    object GroupBox2: TGroupBox
      Left = 16
      Top = 46
      Width = 241
      Height = 113
      TabOrder = 0
      object ComboBox2: TComboBox
        Left = 88
        Top = 68
        Width = 137
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        TabOrder = 0
      end
      object StaticText1: TStaticText
        Left = 20
        Top = 69
        Width = 58
        Height = 17
        Caption = #1044#1086#1073#1072#1074#1080#1090#1100':'
        TabOrder = 1
      end
      object Panel4: TPanel
        Left = 17
        Top = 19
        Width = 208
        Height = 32
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -19
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        TabOrder = 2
      end
    end
    object Button5: TButton
      Left = 16
      Top = 166
      Width = 98
      Height = 25
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100
      TabOrder = 1
      OnClick = Button5Click
    end
    object Button6: TButton
      Left = 152
      Top = 166
      Width = 75
      Height = 25
      Caption = #1054#1090#1084#1077#1085#1072
      TabOrder = 2
      OnClick = Button6Click
    end
    object struktStanka: TStaticText
      Left = 14
      Top = 7
      Width = 65
      Height = 17
      Caption = 'struktStanka'
      TabOrder = 3
    end
  end
  object ABSDatabase1: TABSDatabase
    CurrentVersion = '7.30 '
    DatabaseFileName = '\TehDerevo.ABS'
    DatabaseName = 'TehDerevo'
    Exclusive = False
    MaxConnections = 500
    MultiUser = False
    SessionName = 'Default'
    Left = 672
    Top = 40
  end
  object TB: TABSTable
    CurrentVersion = '7.30 '
    DatabaseName = 'TehDerevo'
    InMemory = False
    ReadOnly = False
    TableName = 'TB'
    Exclusive = False
    Left = 664
    Top = 88
  end
  object Ceh: TABSTable
    CurrentVersion = '7.30 '
    InMemory = False
    ReadOnly = False
    Exclusive = False
    Left = 704
    Top = 88
  end
  object ABSQuery1: TABSQuery
    CurrentVersion = '7.30 '
    DatabaseName = 'TehDerevo'
    InMemory = False
    ReadOnly = False
    Left = 664
    Top = 128
  end
  object Mod: TABSTable
    CurrentVersion = '7.30 '
    InMemory = False
    ReadOnly = False
    Exclusive = False
    Left = 744
    Top = 88
  end
  object PopupMenu1: TPopupMenu
    Left = 624
    Top = 40
    object N1: TMenuItem
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1087#1086#1076#1082#1072#1090#1072#1083#1086#1075
      OnClick = N1Click
    end
    object N2: TMenuItem
      Caption = #1054#1090#1082#1088#1099#1090#1100
      OnClick = N2Click
    end
    object N5: TMenuItem
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100
      Visible = False
      OnClick = N5Click
    end
    object N6: TMenuItem
      Caption = #1048#1079#1084#1077#1085#1080#1090#1100
      OnClick = N6Click
    end
    object N7: TMenuItem
      Caption = #1059#1076#1072#1083#1080#1090#1100
      OnClick = N7Click
    end
    object N8: TMenuItem
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1074#1077#1090#1074#1100
    end
    object N9: TMenuItem
      Caption = #1050#1086#1087#1080#1088#1086#1074#1072#1090#1100' '#1089#1090#1088#1091#1082#1090#1091#1088#1091
      OnClick = N9Click
    end
  end
  object PopupMenu2: TPopupMenu
    Left = 648
    Top = 328
    object NPodkat: TMenuItem
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1087#1086#1076#1082#1072#1090#1077#1075#1086#1088#1080#1102
      Visible = False
      OnClick = NPodkatClick
    end
    object NOpen: TMenuItem
      Caption = #1054#1090#1082#1088#1099#1090#1100
      Visible = False
      OnClick = NOpenClick
    end
    object NDelete: TMenuItem
      Caption = #1059#1076#1072#1083#1080#1090#1100
      OnClick = NDeleteClick
    end
  end
  object ABSQuery2: TABSQuery
    CurrentVersion = '7.30 '
    DatabaseName = 'TehDerevo'
    InMemory = False
    ReadOnly = False
    Left = 704
    Top = 128
  end
  object MainMenu1: TMainMenu
    Left = 624
    Top = 88
    object N1231: TMenuItem
      Caption = #1044#1077#1081#1089#1090#1074#1080#1103
    end
    object N3: TMenuItem
      Caption = #1042#1080#1076
      object N10: TMenuItem
        Caption = #1055#1086' '#1084#1086#1076#1077#1083#1103#1084
        OnClick = N10Click
      end
      object N11: TMenuItem
        Caption = #1055#1086' '#1088#1072#1089#1087#1086#1083#1086#1078#1077#1085#1080#1102
        OnClick = N11Click
      end
    end
    object N4: TMenuItem
      Caption = #1042#1099#1093#1086#1076
      OnClick = N4Click
    end
  end
  object OpenDialog1: TOpenDialog
    Left = 464
    Top = 8
  end
end
