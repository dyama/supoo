; Test script for supoo
(
  (putln "")               ; 空文字列
  (setq title              ; 途中改行
        "supooのテスト")   ; 非英数字
  (putln $title)
  (setq a                  ; 変数定義
        (pow (+ 1 2) 2))   ; べき乗関数
  (put "a = ")             ; 文字列印字
  (putln $a)               ; => 9
  (put "PI * 4 = ")        ;
  (putln (* 4 $pi))        ; 組み込み変数 pi の展開
                           ; => 12.566371
  (putln (mod 10 3))       ; => 1
  (putln (eq 1 1))         ; 比較 ==
  (putln (ne 1 1))         ; 比較 !=
  (putln (gt 1 1))         ; 比較 >
  (putln (lt 1 1))         ; 比較 <
  (putln (ge 1 1))         ; 比較 >=
  (putln (le 1 1))         ; 比較 <=

  (setq hoge 123)
  (setq fuga 123)
  (if (eq $hoge $fuga)     ; if 文
    (quate (put "true"))
    (quate (put "false"))
    )
)

