object frmMain: TfrmMain
  Left = 300
  Top = 300
  BorderIcons = [biSystemMenu, biMinimize]
  Caption = 'Clicking bot 2.4.1'
  ClientHeight = 407
  ClientWidth = 404
  Color = clWindow
  Constraints.MaxWidth = 420
  Constraints.MinHeight = 330
  Constraints.MinWidth = 420
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsStayOnTop
  KeyPreview = True
  OldCreateOrder = False
  Position = poDesigned
  OnClose = FormClose
  OnDestroy = FormDestroy
  OnShow = FormShow
  DesignSize = (
    404
    407)
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 17
    Top = 63
    Width = 64
    Height = 13
    Caption = 'Boja kursora:'
  end
  object Label2: TLabel
    Left = 214
    Top = 63
    Width = 64
    Height = 13
    Caption = 'Boja kursora:'
  end
  object btnOperation: TPanel
    Left = 77
    Top = 369
    Width = 252
    Height = 30
    Anchors = [akLeft, akBottom]
    BevelInner = bvSpace
    BevelKind = bkSoft
    BevelOuter = bvNone
    Caption = 'OUT'
    Color = clRed
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentBackground = False
    ParentFont = False
    TabOrder = 1
    OnMouseDown = btnOperationMouseDown
    OnMouseLeave = btnOperationMouseLeave
    OnMouseUp = btnOperationMouseUp
  end
  object btnCursor1Color: TPanel
    Left = 85
    Top = 59
    Width = 28
    Height = 22
    BevelOuter = bvSpace
    Color = clBlue
    ParentBackground = False
    TabOrder = 2
    OnMouseDown = btnCursor1ColorMouseDown
    OnMouseEnter = btnCursor1ColorMouseEnter
    OnMouseLeave = btnCursor1ColorMouseLeave
    OnMouseUp = btnCursor1ColorMouseUp
  end
  object btnCursor2Color: TPanel
    Left = 282
    Top = 59
    Width = 28
    Height = 22
    BevelOuter = bvSpace
    Color = clYellow
    ParentBackground = False
    TabOrder = 3
    OnMouseDown = btnCursor2ColorMouseDown
    OnMouseEnter = btnCursor2ColorMouseEnter
    OnMouseLeave = btnCursor2ColorMouseLeave
    OnMouseUp = btnCursor2ColorMouseUp
  end
  object listView1: TListView
    Tag = 1
    Left = 8
    Top = 111
    Width = 186
    Height = 198
    Anchors = [akLeft, akTop, akBottom]
    Checkboxes = True
    Columns = <
      item
        Caption = '#'
        Width = 22
      end
      item
        Caption = 'X'
        Width = 40
      end
      item
        Caption = 'Y'
        Width = 40
      end
      item
        Caption = 'a[px]'
        Width = 40
      end
      item
        Caption = 'b[px]'
        Width = 40
      end>
    ColumnClick = False
    GridLines = True
    MultiSelect = True
    RowSelect = True
    TabOrder = 4
    ViewStyle = vsReport
    OnClick = listView1Click
    OnItemChecked = listView1ItemChecked
  end
  object listView2: TListView
    Left = 206
    Top = 111
    Width = 186
    Height = 198
    Anchors = [akLeft, akTop, akBottom]
    Checkboxes = True
    Columns = <
      item
        Caption = '#'
        Width = 22
      end
      item
        Caption = 'X'
        Width = 40
      end
      item
        Caption = 'Y'
        Width = 40
      end
      item
        Caption = 'a[px]'
        Width = 40
      end
      item
        Caption = 'b[px]'
        Width = 40
      end>
    ColumnClick = False
    GridLines = True
    MultiSelect = True
    RowSelect = True
    TabOrder = 5
    ViewStyle = vsReport
    OnClick = listView2Click
    OnItemChecked = listView2ItemChecked
  end
  object btnAdd1: TPanel
    Left = 8
    Top = 89
    Width = 57
    Height = 18
    Hint = 'Dodaj parametre (x,y,a,b) na spisak'
    BevelInner = bvSpace
    BevelKind = bkSoft
    BevelOuter = bvNone
    Caption = '+'
    Color = clWindow
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clInfoText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentBackground = False
    ParentFont = False
    ParentShowHint = False
    ShowHint = True
    TabOrder = 6
    OnMouseDown = btnAdd1MouseDown
    OnMouseEnter = btnAdd1MouseEnter
    OnMouseLeave = btnAdd1MouseLeave
    OnMouseUp = btnAdd1MouseUp
  end
  object btnRemove1: TPanel
    Left = 71
    Top = 89
    Width = 57
    Height = 18
    Hint = 'Obri'#353'i selektovanu stavku sa spiska'
    BevelInner = bvSpace
    BevelKind = bkSoft
    BevelOuter = bvNone
    Caption = '-'
    Color = clWindow
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clInfoText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentBackground = False
    ParentFont = False
    ParentShowHint = False
    ShowHint = True
    TabOrder = 7
    OnMouseDown = btnRemove1MouseDown
    OnMouseEnter = btnRemove1MouseEnter
    OnMouseLeave = btnRemove1MouseLeave
    OnMouseUp = btnRemove1MouseUp
  end
  object btnRemove2: TPanel
    Left = 272
    Top = 90
    Width = 57
    Height = 18
    Hint = 'Obri'#353'i selektovanu stavku sa spiska'
    BevelInner = bvSpace
    BevelKind = bkSoft
    BevelOuter = bvNone
    Caption = '-'
    Color = clWindow
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clInfoText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentBackground = False
    ParentFont = False
    ParentShowHint = False
    ShowHint = True
    TabOrder = 8
    OnMouseDown = btnRemove2MouseDown
    OnMouseEnter = btnRemove2MouseEnter
    OnMouseLeave = btnRemove2MouseLeave
    OnMouseUp = btnRemove2MouseUp
  end
  object btnAdd2: TPanel
    Left = 206
    Top = 90
    Width = 57
    Height = 18
    Hint = 'Dodaj parametre (x,y,a,b) na spisak'
    BevelInner = bvSpace
    BevelKind = bkSoft
    BevelOuter = bvNone
    Caption = '+'
    Color = clWindow
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clInfoText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentBackground = False
    ParentFont = False
    ParentShowHint = False
    ShowHint = True
    TabOrder = 9
    OnMouseDown = btnAdd2MouseDown
    OnMouseEnter = btnAdd2MouseEnter
    OnMouseLeave = btnAdd2MouseLeave
    OnMouseUp = btnAdd2MouseUp
  end
  object upDown1: TUpDown
    Left = 112
    Top = 59
    Width = 17
    Height = 22
    Hint = 'Produ'#382'ava/skra'#263'uje virtuelni kursor'
    Min = 107
    Max = 200
    Increment = 2
    ParentShowHint = False
    Position = 107
    ShowHint = True
    TabOrder = 10
    OnClick = upDown1Click
  end
  object upDown2: TUpDown
    Left = 310
    Top = 59
    Width = 17
    Height = 22
    Hint = 'Produ'#382'ava/skra'#263'uje virtuelni kursor'
    Min = 107
    Max = 200
    Increment = 2
    ParentShowHint = False
    Position = 107
    ShowHint = True
    TabOrder = 11
    OnClick = upDown2Click
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 4
    Width = 384
    Height = 45
    Caption = 'Prozor'
    TabOrder = 0
    object Label5: TLabel
      Left = 10
      Top = 19
      Width = 10
      Height = 13
      Caption = 'X:'
    end
    object Label6: TLabel
      Left = 76
      Top = 19
      Width = 10
      Height = 13
      Caption = 'Y:'
    end
    object Label7: TLabel
      Left = 143
      Top = 19
      Width = 53
      Height = 13
      Caption = 'Du'#382'ina (a):'
    end
    object Label8: TLabel
      Left = 245
      Top = 19
      Width = 48
      Height = 13
      Caption = 'Visina (b):'
    end
    object txtXcoord: TEdit
      Left = 22
      Top = 17
      Width = 40
      Height = 21
      NumbersOnly = True
      TabOrder = 0
    end
    object txtYcoord: TEdit
      Left = 88
      Top = 17
      Width = 40
      Height = 21
      NumbersOnly = True
      TabOrder = 1
    end
    object txtWidth: TEdit
      Left = 200
      Top = 16
      Width = 30
      Height = 21
      NumbersOnly = True
      TabOrder = 2
    end
    object txtHeight: TEdit
      Left = 297
      Top = 16
      Width = 30
      Height = 21
      NumbersOnly = True
      TabOrder = 3
    end
    object btnWhere: TButton
      Left = 340
      Top = 15
      Width = 36
      Height = 23
      Caption = 'Gde?'
      TabOrder = 4
      OnClick = btnWhereClick
    end
  end
  object cbTargetNum1: TComboBox
    Left = 145
    Top = 82
    Width = 49
    Height = 21
    ItemHeight = 13
    TabOrder = 12
    OnKeyDown = cbTargetNum1KeyDown
  end
  object cbTargetNum2: TComboBox
    Left = 343
    Top = 83
    Width = 49
    Height = 21
    ItemHeight = 13
    TabOrder = 13
    OnKeyDown = cbTargetNum2KeyDown
  end
  object GroupBox2: TGroupBox
    Left = 8
    Top = 315
    Width = 384
    Height = 41
    Anchors = [akLeft, akBottom]
    Caption = 'Pode'#353'avanja'
    TabOrder = 14
    object Label3: TLabel
      Left = 171
      Top = 18
      Width = 67
      Height = 13
      Caption = 'Tra'#382'ena boja:'
    end
    object Label4: TLabel
      Left = 297
      Top = 18
      Width = 38
      Height = 13
      Caption = 'Pre'#269'ica:'
    end
    object chkFreeze: TCheckBox
      Left = 18
      Top = 16
      Width = 50
      Height = 17
      Caption = 'Freeze'
      TabOrder = 0
      OnClick = chkFreezeClick
    end
    object chkOcrMode: TCheckBox
      Left = 97
      Top = 16
      Width = 46
      Height = 17
      Caption = 'OCR'
      Checked = True
      State = cbChecked
      TabOrder = 1
    end
    object btnSearchColor: TPanel
      Left = 244
      Top = 15
      Width = 35
      Height = 18
      BevelOuter = bvSpace
      Color = clLime
      ParentBackground = False
      TabOrder = 2
      OnMouseDown = btnSearchColorMouseDown
      OnMouseEnter = btnSearchColorMouseEnter
      OnMouseLeave = btnSearchColorMouseLeave
      OnMouseUp = btnSearchColorMouseUp
    end
    object txtShortcut: TEdit
      Left = 340
      Top = 14
      Width = 23
      Height = 21
      CharCase = ecUpperCase
      MaxLength = 1
      TabOrder = 3
    end
  end
  object btnAddCombo1: TButton
    Left = 145
    Top = 65
    Width = 24
    Height = 17
    Hint = 'Dodaj vrednost u listu'
    Caption = '+'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 15
    OnClick = btnAddCombo1Click
  end
  object btnAddCombo2: TButton
    Left = 342
    Top = 65
    Width = 26
    Height = 17
    Hint = 'Dodaj vrednost u listu'
    Caption = '+'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 16
    OnClick = btnAddCombo2Click
  end
  object btnClearCombo1: TButton
    Left = 170
    Top = 65
    Width = 24
    Height = 17
    Hint = 'Obri'#353'i vrednost iz liste'
    Caption = '-'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 17
    OnClick = btnClearCombo1Click
  end
  object btnClearCombo2: TButton
    Left = 367
    Top = 65
    Width = 26
    Height = 17
    Hint = 'Obri'#353'i vrednost iz liste'
    Caption = '-'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 18
    OnClick = btnClearCombo2Click
  end
  object dlgColor: TColorDialog
    Left = 363
    Top = 364
  end
end
