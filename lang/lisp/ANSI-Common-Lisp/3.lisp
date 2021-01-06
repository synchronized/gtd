;; 使用 car 与 cdr 来定义一个函数，返回一个列表的第四个元素。

(defun nth-4 (lst)
  (car (cdr (cdr (cdr lst)))))
