(defun test1 ()
  (+ (- 5 1) (+ 3 7)))

(defun test2 ()
  (list 1 (+ 2 3)))

(defun test3 ()
  (if (listp 1) (+ 1 2) (+ 3 4)))

(defun test4 ()
  (list (and (listp 3) t) (+ 1 2)))
