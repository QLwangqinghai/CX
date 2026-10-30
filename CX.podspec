Pod::Spec.new do |s|
  s.name             = 'CX'
  s.version          = '0.1.0'
  s.summary          = 'CX.'

  s.description      = 'CX.'

  s.homepage         = 'https://github.com/QLwangqinghai/CX'
  s.license  = { :type => 'MIT'}
  s.author           = { '' => '' }
  s.source           = { :git => 'https://github.com/QLwangqinghai/CX.git', :tag => "#{s.version}"}

  s.ios.deployment_target = '12.0'
  s.osx.deployment_target = "12.0"
  
  s.public_header_files = "Sources/CX/include/*.h"
  s.source_files = "Sources/CX/**/*.{h,c,m,cpp}"

end
