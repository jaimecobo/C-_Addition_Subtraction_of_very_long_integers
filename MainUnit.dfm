object FormMain: TFormMain
  Left = 192
  Top = 115
  Width = 503
  Height = 212
  Caption = 'Números largos'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnActivate = FormActivate
  PixelsPerInch = 96
  TextHeight = 13
  object ButtonMenos: TButton
    Left = 208
    Top = 112
    Width = 65
    Height = 49
    Caption = '-'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -24
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
    OnClick = ButtonMenosClick
  end
  object ButtonMas: TButton
    Left = 88
    Top = 112
    Width = 65
    Height = 49
    Caption = '+'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -24
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 1
    OnClick = ButtonMasClick
  end
  object ButtonCE: TButton
    Left = 328
    Top = 112
    Width = 65
    Height = 49
    Caption = 'CE'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 2
    OnClick = ButtonCEClick
  end
  object MemoDisplay1: TMemo
    Left = 8
    Top = 8
    Width = 473
    Height = 25
    Alignment = taRightJustify
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    Lines.Strings = (
      'Memo1')
    MaxLength = 58
    ParentFont = False
    TabOrder = 3
    WantReturns = False
  end
  object MemoDisplay2: TMemo
    Left = 8
    Top = 40
    Width = 473
    Height = 25
    Alignment = taRightJustify
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    Lines.Strings = (
      'Memo1')
    MaxLength = 58
    ParentFont = False
    TabOrder = 4
    WantReturns = False
  end
  object MemoDisplay3: TMemo
    Left = 8
    Top = 72
    Width = 473
    Height = 25
    Alignment = taRightJustify
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    Lines.Strings = (
      'Memo1')
    MaxLength = 58
    ParentFont = False
    TabOrder = 5
    WantReturns = False
  end
  object Button1: TButton
    Left = 448
    Top = 136
    Width = 33
    Height = 25
    Caption = 'Off'
    TabOrder = 6
    OnClick = Button1Click
  end
end
