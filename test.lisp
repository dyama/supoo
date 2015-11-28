; Test script for supoo
(
  (setq title "supooのテスト")
  (putln $title)
  (setq a (pow (+ 1 2) 2)) ; 定義
  (put "a =")              ; 文字列
  (putln $a)               ; => 9
  (put "PI * 4 =")         ;
  (putln (* 4 $pi))        ; 組み込み変数 pi の展開
                           ; => 12.566371
  (putln (mod 10 3))
)

