#include "PushButton.hpp"
#include "Skin.hpp"

namespace zn
{
namespace ui
{
	PushButton::PushButton() : AComposite()
	{
		r_text = new Text();
		r_text->setPadding(Padding(4,4,4,4));
		add(r_text);
	}

	void PushButton::setText(const std::string &str)
	{
		r_text->setText(str);
	}

	void PushButton::renderSelf(IRenderer &r)
	{
		// TODO PushButton: find a way to let the skin draw text
		r_skin->drawPushButton(r, *this);
	}

	void PushButton::onSizeChanged()
	{
		r_text->setLocalBounds(IntRect(
			0, 0, m_localBounds.width()-1, m_localBounds.height()-1));
	}

	void PushButton::onPress()
	{
		onPressSignal();
	}

	void PushButton::onRelease()
	{
		onReleaseSignal();
		onClickSignal();
	}

} // namespace ui
} // namespace zn


