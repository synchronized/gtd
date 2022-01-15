#-*- coding:utf-8 -*-

import smtplib
from email.header import Header
from email.mime.text import MIMEText


mailto_list = ['synchronized@yeah.net']
# mail_host = 'smtp.qq.com' #服务器
# mail_user = 'httpservletcontext@qq.com' #用户名
# mail_pass = 'scavcpfaibfsbbif' #密码
# mail_postfix = 'qq.com' #发件箱的后缀
mail_host = 'smtp.exmail.qq.com' #服务器
mail_user = 'sunda@zs-e.com' #用户名
mail_from = 'sunda@zs-e.com'
mail_pass = 'ZSsd94hpgHD' #密码
mail_postfix = 'sz-e.com' #发件箱的后缀

def send_mail(to_list, sub, content):
    me = "hello<%s@%s>" % (mail_user, mail_postfix)
    msg = MIMEText(content, _subtype='plain', _charset='utf-8')
    msg['Subject'] = Header(sub, 'utf-8')
    msg['From'] = mail_from
    msg['To'] = ';'.join(to_list)

    try:
        server = smtplib.SMTP_SSL()
        server.set_debuglevel(True)
        server.connect(mail_host)
        server.login(mail_user, mail_pass)
        server.sendmail(me, to_list, msg.as_string())
        server.quit()
        return True
    except Exception, e:
        print str(e)
        return False

if __name__ == '__main__':
    if send_mail(mailto_list, "你的的数据线忘在公司了", "你的的数据线忘在公司了"):
        print '发送成功'
    else:
        print '发送失败';
