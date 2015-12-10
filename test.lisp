;;;; Test script for supoo
(
  ;;; 基本関数
  (defun test1 (
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
      (putln "true")
      (putln "false")
    )

    (defun myfunc (          ; 関数定義
      (putln "function called.")
    ))
    (myfunc 1 2)             ; 関数呼び出し(仮引数代入は未実装)
  ))
  ;(test1)

  ;;; 組み込み関数の別名
  (defun test2 (
    (putln (add 1 2))
    (putln (+ 1 2))
    (putln (>= 1 2))
    (putln (< 1 2))
    (putln (** 2 3))
    (putln (% 2 3))
  ))
  ;(test2)

  ;;; 関数の再帰呼び出しによるループ
  (setq c 0)
  (defun loop (
    (putln $c)
    (setq c (+ $c 1))
    (if (lt $c 10)
      (loop)
    )
  ))
  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;(loop)

  ;;; 遅延評価テスト
  (defun "遅延評価テスト" (
    (defun check_value (
      (if (eq $a 3)
        (putln "a is 3!")
        (putln "a is not 3!")
      )
    ))
    (setq a 4)
    (check_value) 
    (setq a 3)
    (check_value) 
  ))
  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;("遅延評価テスト")

  ;;; 数学関数
  (defun math-funcs (
    (put "sin(1) = ")
    (putln (sin 1))
    (put "cos(1) = ")
    (putln (cos 1))
    (put "tan(1) = ")
    (putln (tan 1))
  ))
  ;(math-funcs)

  ; リスト操作
  (defun test-list (
    (setq ary ("foo" "bar" "baz"))
    (put "Size of array is ")
    (putln (len $ary))
    (put "Second element is ")
    (putln (ref $ary 1))
    ; push/pop
    (push $ary "hoge")
    (setq hoge (pop $ary))
    (putln $hoge)
    ; shift/unshift
    (unshift $ary 123)
    (setq number (shift $ary))
    (putln $number)
  ))
  ;;;;;;;;;;;;;;;;;;(test-list)
  
  ; ループ構文的な関数のテスト
  (defun looptest (
    ; 変数初期化
    (setq i 0)
    ; while 文(関数)
    (while (lt $i 10) (
      (put $i)
      (put " ")
      (setq i (+ $i 1))
    ))
    (putln "")
  ))
  ;;;;;;;;;;;;;;;;;;;;(looptest)
  
  ;(setq flag1 $true)
  ;(setq flag2 $false)
  ;(putln $flag1)
  ;(putln $flag2)
  ;(setq foo (int 1.23))
  ;(dump $foo)
)

