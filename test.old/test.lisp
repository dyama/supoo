(
  (dump "hoge")
  (defun myfunc (
    (putln $1) 
    (putln $2) 
    (putln $3) 
    (putln $4) 
  ))
  (myfunc 123 345 567)
  (putln $1)
)
